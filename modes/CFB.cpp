#include "CFB.hpp"

/**
 * CFB primary constructor
 *
 * @param blockCipher a reference to a BlockCipher that will be used to encrypt/decrypt data
 * @param iv the iv used during encryption/decryption
 * @param ivSize the size of the iv
 *
 * @throws std::invalid_argument if blockCipher and iv don't have the same size
 */
CFB::CFB(const BlockCipher &blockCipher, const uint8_t iv[], uint8_t ivSize) : StreamModeOfOperation(blockCipher), ivSize(ivSize) {
    if (blockCipher.getBlockSize() != ivSize)
        throw std::invalid_argument("blockCipher and iv must have the same blockSize");

    for (int i = 0; i < ivSize; i++)
        this->iv[i] = iv[i];
}

/**
 * CFB copy constructor
 *
 * @param that reference to a preexisting CFB object that should be copied
 */
CFB::CFB(const CFB &that) : CFB(that.blockCipher, that.iv, that.ivSize) {

}

/**
 * CFB destructor
 */
CFB::~CFB() {

}

/**
 * takes data from a plaintext stream, encrypts, and writes it to a ciphertext stream 
 *
 * algorithm briefly described at: https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation
 *
 * @param plaintext std::istream where data is retrieved for encryption
 * @param ciphertext std::ostream where data is sent after padding and encrypting
 *
 * @throws std::bad_alloc if unable to allocate memory on the heap for buffers
 */
void CFB::encrypt(std::istream &plaintext, std::ostream &ciphertext) const {
    uint8_t blockSize, *buffer, *prev, nbytes;

    blockSize = blockCipher.getBlockSize();
    try {
        buffer = new uint8_t[blockSize];
        prev = new uint8_t[blockSize];
    } catch (std::bad_alloc &e) {
        throw;
    }

    // read first block of plaintext
    plaintext.read((char*) buffer, blockSize);
    nbytes = plaintext.gcount();

    // prepare iv
    for (uint8_t i = 0; i < blockSize; i++)
        prev[i] = iv[i];

    while (plaintext.peek() != EOF) {
        // encrypt previous round's ciphertext
        blockCipher.encryptBlock(prev, prev);

        // XOR plaintext with the previous round's encrypted ciphertext
        for (uint8_t i = 0; i < blockSize; i++)
            buffer[i] ^= prev[i];

        // write it to the output stream
        ciphertext.write((char*) buffer, blockSize);

        // save this round's ciphertext
        for (uint8_t i = 0; i < blockSize; i++)
            prev[i] = buffer[i];

        // read next block of plaintext
        plaintext.read((char*) buffer, blockSize);
        nbytes = plaintext.gcount();
    }

    // encrypt previous round's ciphertext
    blockCipher.encryptBlock(prev, prev);

    // XOR plaintext with the previous round's encrypted ciphertext
    for (uint8_t i = 0; i < nbytes; i++)
        buffer[i] ^= prev[i];
    
    // write it to the output stream
    ciphertext.write((char*) buffer, nbytes);

    delete buffer;
    delete prev;
}

/**
 * takes data from a ciphertext stream, decrypts, and writes it to a plaintext stream 
 *
 * algorithm briefly described at: https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation
 *
 * @param ciphertext std::istream where data is retrieved for decryption
 * @param plaintext std::ostream where data is sent after decrypting and stripping padding
 *
 * @throws std::bad_alloc if unable to allocate memory on the heap for buffers
 */
void CFB::decrypt(std::istream &ciphertext, std::ostream &plaintext) const {
    uint8_t blockSize, *buffer, *prev, *next, nbytes;

    blockSize = blockCipher.getBlockSize();

    try {
        buffer = new uint8_t[blockSize];
        prev = new uint8_t[blockSize];
        next = new uint8_t[blockSize];
    } catch (std::bad_alloc &e) {
        throw;
    } 

    // read first block of ciphertext
    ciphertext.read((char*) buffer, blockSize);
    nbytes = ciphertext.gcount();

    // prepare iv
    for (uint8_t i = 0; i < blockSize; i++)
        prev[i] = iv[i];

    while (ciphertext.peek() != EOF) {
        // save this round's ciphertext
        for (uint8_t i = 0; i < blockSize; i++)
            next[i] = buffer[i];
        
        // encrypt previous round's ciphertext
        blockCipher.encryptBlock(prev, prev);
        
        // XOR ciphertext with the previous round's encrypted ciphertext
        for (uint8_t i = 0; i < blockSize; i++) {
            buffer[i] ^= prev[i];
            prev[i] = next[i];
        }

        // write it to the output stream
        plaintext.write((char*) buffer, blockSize);

        // read next block of ciphertext
        ciphertext.read((char*) buffer, blockSize);
        nbytes = ciphertext.gcount();
    }

    if (nbytes) {
        // encrypt previous round's ciphertext
        blockCipher.encryptBlock(prev, prev);
            
        // XOR ciphertext with the previous round's encrypted ciphertext
        for (uint8_t i = 0; i < nbytes; i++)
            buffer[i] ^= prev[i];

        // write it to the output stream
        plaintext.write((char*) buffer, nbytes);
    }

    delete buffer;
    delete prev;
    delete next;
}