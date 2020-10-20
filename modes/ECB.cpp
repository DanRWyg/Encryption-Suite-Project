/**
 * class implementation for the ECB mode of operation.
 * @file ECB.cpp
 * @author Daniel Wygant
 * @version 1.0 10/20/2020
 */

#include "ECB.hpp"

/**
 * ECB primary constructor
 *
 * @param blockCipher a reference to a BlockCipher that will be used to encrypt/decrypt data
 * @param blockPadding a reference to a BlockPadding that will be used to pad/unpad data to a multiple of blockSize
 *
 * @throws std::invalid_argument if blockCipher and blockPadding don't have the same blockSize
 */
ECB::ECB(const BlockCipher &blockCipher, const BlockPadding &blockPadding) : BlockModeOfOperation(blockCipher, blockPadding) {
    
}

/**
 * ECB copy constructor
 *
 * @param that reference to a preexisting ECB object that should be copied
 */
ECB::ECB(const ECB &that) : ECB(that.blockCipher, that.blockPadding) {

}

/**
 * ECB destructor
 */
ECB::~ECB() {

}

/**
 * takes data from a plaintext stream, applies padding, encrypts, and writes it to a ciphertext stream 
 *
 * algorithm briefly described at: https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation
 *
 * @param plaintext std::istream where data is retrieved for encryption
 * @param ciphertext std::ostream where data is sent after padding and encrypting
 *
 * @throws std::bad_alloc if unable to allocate memory on the heap for buffers
 */
void ECB::encrypt(std::istream &plaintext, std::ostream &ciphertext) const {
    uint8_t blockSize, *buffer, nbytes, *padding;

    blockSize = blockCipher.getBlockSize();
    try {
        buffer = new uint8_t[blockSize];
    } catch (std::bad_alloc &e) {
        throw;
    }

    // read first block of plaintext
    plaintext.read((char*) buffer, blockSize);
    nbytes = plaintext.gcount();

    while (plaintext.peek() != EOF) {
        // encrypt plaintext block and write it to the output stream
        blockCipher.encryptBlock(buffer, buffer);
        ciphertext.write((char*) buffer, blockSize);

        // read next block of plaintext
        plaintext.read((char*) buffer, blockSize);
        nbytes = plaintext.gcount();
    }

    // the last bytes of plaintext may not be enough to fill a full block so we should add padding
    // depending on the padding scheme, an additional full block of padding may be needed
    try {
        padding = blockPadding.addPadding(buffer, nbytes);
    } catch (std::bad_alloc &e) {
        throw;
    }
    
    // encrypt the plaintext block and write it to the output stream
    blockCipher.encryptBlock(buffer, buffer);
    ciphertext.write((char*) buffer, blockSize);

    // if the padding scheme required an additional full block of padding, encrypt it and write it to the output stream
    if (padding) {
        blockCipher.encryptBlock(padding, padding);
        ciphertext.write((char*) padding, blockSize);

        delete padding;
    }

    delete buffer;
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
void ECB::decrypt(std::istream &ciphertext, std::ostream &plaintext) const {
    uint8_t blockSize, *buffer, padding;

    blockSize = blockCipher.getBlockSize();
    try {
        buffer = new uint8_t[blockSize];
    } catch (std::bad_alloc &e) {
        throw;
    }
    
    // read first block of ciphertext
    ciphertext.read((char*) buffer, blockSize);

    while (ciphertext.peek() != EOF) {
        // decrypt ciphertext block and write it to the output stream
        blockCipher.decryptBlock(buffer, buffer);
        plaintext.write((char*) buffer, blockSize);

        // read the next block of ciphertext
        ciphertext.read((char*) buffer, blockSize);
    }

    // decrypt ciphertext block
    blockCipher.decryptBlock(buffer, buffer);

    // strip padding and write it to the output stream
    padding = blockPadding.getPaddingAmount(buffer);
    if (padding != blockSize)
        plaintext.write((char*) buffer, blockSize - padding);

    delete buffer;
}