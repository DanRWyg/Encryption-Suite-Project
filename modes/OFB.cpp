#include "OFB.hpp"

/**
 * OFB primary constructor
 *
 * @param blockCipher a reference to a BlockCipher that will be used to encrypt/decrypt data
 * @param iv the iv used during encryption/decryption
 * @param ivSize the size of the iv
 *
 * @throws std::invalid_argument if blockCipher and iv don't have the same size
 */
OFB::OFB(const BlockCipher &blockCipher, const uint8_t iv[], uint8_t ivSize) : StreamModeOfOperation(blockCipher), ivSize(ivSize) {
    if (blockCipher.getBlockSize() != ivSize)
        throw std::invalid_argument("blockCipher and iv must have the same blockSize");

    for (int i = 0; i < ivSize; i++)
        this->iv[i] = iv[i];
}

/**
 * OFB copy constructor
 *
 * @param that reference to a preexisting OFB object that should be copied
 */
OFB::OFB(const OFB &that) : OFB(that.blockCipher, that.iv, that.ivSize) {

}

/**
 * OFB destructor
 */
OFB::~OFB() {

}

/**
 * takes data from a plaintext stream, encrypts, and writes it to a ciphertext stream 
 * this algorithm is symmetrical so encryption = decryption
 *
 * algorithm briefly described at: https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation
 *
 * @param plaintext std::istream where data is retrieved for encryption
 * @param ciphertext std::ostream where data is sent after padding and encrypting
 *
 * @throws std::bad_alloc if unable to allocate memory on the heap for buffers
 */
void OFB::encrypt(std::istream &plaintext, std::ostream &ciphertext) const {
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
        // encrypt iv (again)
        blockCipher.encryptBlock(prev, prev);

        // XOR plaintext with this round's encrypted iv
        for (uint8_t i = 0; i < blockSize; i++)
            buffer[i] ^= prev[i];

        // write it to the output stream
        ciphertext.write((char*) buffer, blockSize);

        // read next block of plaintext
        plaintext.read((char*) buffer, blockSize);
        nbytes = plaintext.gcount();
    }

    // encrypt iv (again)
    blockCipher.encryptBlock(prev, prev);

    // XOR plaintext with this round's encrypted iv
    for (uint8_t i = 0; i < nbytes; i++)
        buffer[i] ^= prev[i];
    
    // write it to the output stream
    ciphertext.write((char*) buffer, nbytes);

    delete buffer;
    delete prev;
}

/**
 * takes data from a ciphertext stream, decrypts, and writes it to a plaintext stream 
 * this algorithm is symmetrical so encryption = decryption
 *
 * algorithm briefly described at: https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation
 *
 * @param ciphertext std::istream where data is retrieved for decryption
 * @param plaintext std::ostream where data is sent after decrypting and stripping padding
 *
 * @throws std::bad_alloc if unable to allocate memory on the heap for buffers
 */
void OFB::decrypt(std::istream &ciphertext, std::ostream &plaintext) const {
    encrypt(ciphertext, plaintext);
}