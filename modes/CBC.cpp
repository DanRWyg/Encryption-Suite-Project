#include "CBC.hpp"

/**
 * CBC primary constructor
 *
 * @param blockCipher a reference to a BlockCipher that will be used to encrypt/decrypt data
 * @param blockPadding a reference to a BlockPadding that will be used to pad/unpad data to a multiple of blockSize
 * @param iv the iv used during encryption/decryption
 * @param ivSize the size of the iv
 *
 * @throws std::invalid_argument if blockCipher, blockPadding and iv don't have the same size
 */
CBC::CBC(const BlockCipher &blockCipher, const BlockPadding &blockPadding, const uint8_t iv[], uint8_t ivSize) : BlockModeOfOperation(blockCipher, blockPadding), ivSize(ivSize) {
    if (blockCipher.getBlockSize() != ivSize)
        throw std::invalid_argument("blockCipher and iv must have the same blockSize");

    for (int i = 0; i < ivSize; i++)
        this->iv[i] = iv[i];
}

/**
 * CBC copy constructor
 *
 * @param that reference to a preexisting CBC object that should be copied
 */
CBC::CBC(const CBC &that) : CBC(that.blockCipher, that.blockPadding, that.iv, that.ivSize) {

}

/**
 * CBC destructor
 */
CBC::~CBC() {

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
void CBC::encrypt(std::istream &plaintext, std::ostream &ciphertext) const {
    uint8_t blockSize, *buffer, *prev, nbytes, *padding;

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
        // XOR plaintext with previous round's ciphertext
        for (uint8_t i = 0; i < blockSize; i++)
            buffer[i] ^= prev[i];

        // encrypt plaintext block and write it to the output stream
        blockCipher.encryptBlock(buffer, buffer);
        ciphertext.write((char*) buffer, blockSize);

        // save this round's ciphertext
        for (uint8_t i = 0; i < blockSize; i++)
            prev[i] = buffer[i];

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

    // XOR plaintext with previous round's ciphertext
    for (uint8_t i = 0; i < blockSize; i++)
        buffer[i] ^= prev[i];

    // encrypt the plaintext block and write it to the output stream
    blockCipher.encryptBlock(buffer, buffer);
    ciphertext.write((char*) buffer, blockSize);

    // if the padding scheme required an additional full block of padding, encrypt it and write it to the output stream
    if (padding) {
        for (uint8_t i = 0; i < blockSize; i++)
            padding[i] ^= buffer[i];

        blockCipher.encryptBlock(padding, padding);
        ciphertext.write((char*) padding, blockSize);
        delete padding;
    }
    delete buffer;
    delete prev;
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
void CBC::decrypt(std::istream &ciphertext, std::ostream &plaintext) const {
    uint8_t blockSize, *buffer, *prev, *next, padding;

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

    // prepare iv
    for (uint8_t i = 0; i < blockSize; i++)
        prev[i] = iv[i];

    while (ciphertext.peek() != EOF) {
        // save this round's ciphertext
        for (uint8_t i = 0; i < blockSize; i++)
            next[i] = buffer[i];
        
        // decrypt ciphertext block
        blockCipher.decryptBlock(buffer, buffer);
        
        // XOR plaintext with last round's ciphertext
        for (uint8_t i = 0; i < blockSize; i++) {
            buffer[i] ^= prev[i];
            prev[i] = next[i];
        }

        // write plaintext to output stream
        plaintext.write((char*) buffer, blockSize);

        // read next block of ciphertext
        ciphertext.read((char*) buffer, blockSize);
    }

    // decrypt ciphertext block
    blockCipher.decryptBlock(buffer, buffer);
        
    // XOR plaintext with last round's ciphertext
    for (uint8_t i = 0; i < blockSize; i++)
        buffer[i] ^= prev[i];

    // strip padding and write it to the output stream
    padding = blockPadding.getPaddingAmount(buffer);
    if (padding != blockSize)
        plaintext.write((char*) buffer, blockSize - padding);

    delete buffer;
    delete prev;
    delete next;
}