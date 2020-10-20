#include "CTR.hpp"

/**
 * CTR primary constructor
 *
 * @param blockCipher a reference to a BlockCipher that will be used to encrypt/decrypt data
 * @param iv the iv used during encryption/decryption
 * @param ivSize the size of the iv
 *
 * @throws std::invalid_argument if blockCipher and iv don't have the same size
 */
CTR::CTR(const BlockCipher &blockCipher, const uint8_t iv[], uint8_t ivSize) : StreamModeOfOperation(blockCipher), ivSize(ivSize) {
    if (blockCipher.getBlockSize() != ivSize)
        throw std::invalid_argument("blockCipher and iv must have the same blockSize");

    for (int i = 0; i < ivSize; i++)
        this->iv[i] = iv[i];
}

/**
 * CTR copy constructor
 *
 * @param that reference to a preexisting CTR object that should be copied
 */
CTR::CTR(const CTR &that) : CTR(that.blockCipher, that.iv, that.ivSize) {

}

/**
 * CTR destructor
 */
CTR::~CTR() {

}

/**
 * takes data from a plaintext stream, applies padding and encryption, and writes it to a ciphertext stream 
 *
 * algorithm briefly described at: https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation
 *
 * @param plaintext std::istream where data is retrieved for encryption
 * @param ciphertext std::ostream where data is sent after padding and encrypting
 *
 * @throws std::bad_alloc if unable to allocate memory on the heap for buffers
 */
void CTR::encrypt(std::istream &plaintext, std::ostream &ciphertext) const {
    uint8_t blockSize, *buffer, *ctr, *temp, nbytes;

    blockSize = blockCipher.getBlockSize();
    try {
        buffer = new uint8_t[blockSize];
        ctr = new uint8_t[blockSize];
        temp = new uint8_t[blockSize];
    } catch (std::bad_alloc &e) {
        throw;
    }

    // read first block of plaintext
    plaintext.read((char*) buffer, blockSize);
    nbytes = plaintext.gcount();

    // prepare iv/ctr
    for (uint8_t i = 0; i < blockSize; i++)
        ctr[i] = iv[i];

    while (plaintext.peek() != EOF) {
        // encrypt iv/ctr
        blockCipher.encryptBlock(ctr, temp);

        // XOR plaintext with encrypted iv/ctr
        for (uint8_t i = 0; i < blockSize; i++)
            buffer[i] ^= temp[i];

        // write it to the output stream
        ciphertext.write((char*) buffer, blockSize);

        // increment iv/ctr by 1
        for (uint8_t i = blockSize - 1; i >= 0; i--)
            if (++ctr[i])
                break;

        // read next block of plaintext
        plaintext.read((char*) buffer, blockSize);
        nbytes = plaintext.gcount();
    }

    // encrypt iv/ctr
    blockCipher.encryptBlock(ctr, temp);

    // XOR plaintext with encrypted iv/ctr
    for (uint8_t i = 0; i < nbytes; i++)
        buffer[i] ^= temp[i];
    
    // write it to the output stream
    ciphertext.write((char*) buffer, blockSize);

    delete buffer;
    delete ctr;
    delete temp;
}

/**
 * takes data from a ciphertext stream, decrypts and strips padding, and writes it to a plaintext stream 
 *
 * algorithm briefly described at: https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation
 *
 * @param ciphertext std::istream where data is retrieved for decryption
 * @param plaintext std::ostream where data is sent after decrypting and stripping padding
 *
 * @throws std::bad_alloc if unable to allocate memory on the heap for buffers
 */
void CTR::decrypt(std::istream &ciphertext, std::ostream &plaintext) const {
    encrypt(ciphertext, plaintext);
}