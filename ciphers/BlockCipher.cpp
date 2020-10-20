/**
 * class implementation for the abstract block cipher superclass.
 * @file BlockCipher.cpp
 * @author Daniel Wygant
 * @version 1.0 10/20/2020
 */

#include "BlockCipher.hpp"

/**
 * BlockCipher primary constructor
 *
 * @param blockSize the size in bytes of this block cipher's unit of encryption/decryption
 *
 * @throws std::out_of_range if blockSize is 0
 */
BlockCipher::BlockCipher(uint8_t blockSize) : blockSize(blockSize) {
    if (blockSize == 0)
        throw std::out_of_range("blockSize must be greater than 0");
}

/**
 * Block Cipher destructor
 */
BlockCipher::~BlockCipher() {
    
}

/**
 * @return [BlockCipher::blockSize]
 */
uint8_t BlockCipher::getBlockSize() const {
    return blockSize;
}