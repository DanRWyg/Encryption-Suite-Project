/**
 * class implementation for the PKCS#5 block padding standard.
 * @file PKCS_5.cpp
 * @author Daniel Wygant
 * @version 1.0 10/20/2020
 */

#include "PKCS_5.hpp"

/**
 * PKCS_5 primary constructor
 * 
 * @param blockSize the size in bytes used to calculate the appropriate amount of padding
 *
 * @throws std::out_of_range if blockSize is 0
 */
PKCS_5::PKCS_5(uint8_t blockSize) : BlockPadding(blockSize) {

}

/**
 *PKCS_5 copy constructor
 *
 * @param that the reference to a preexisting PKCS_5 object that should be copied
 */
PKCS_5::PKCS_5(const PKCS_5 &that) : PKCS_5(that.blockSize) {
    
}

/**
 * PKCS_5 destructor
 */
PKCS_5::~PKCS_5() {

}

/**
 * calculates and applies necessary padding for param block in order to make the number of data bytes a multiple of [PKCS_5::blockSize]
 * 
 * implements the PKCS#5 padding scheme briefly described at: https://en.wikipedia.org/wiki/Padding_(cryptography)
 *
 * @param block the block of bytes containing data that needs to be padded
 * @param dataSize the number of data bytes present in param block
 *
 * @return a full block of padding if the number of data bytes is already a multiple of [PKCS_5::blockSize] and nullptr otherwise
 *
 * @throws std::bad_alloc if unable to allocate memory for return block
 */
uint8_t* PKCS_5::addPadding(uint8_t block[], uint8_t dataSize) const {
    uint8_t *padding = nullptr;

    if (dataSize == blockSize) {
        try {
            padding = new uint8_t[blockSize];
        } catch (std::bad_alloc &e) {
            throw;
        }
        for (int i = 0; i < blockSize; i++)
            padding[i] = blockSize;
    }

    for (int i = 0; i < blockSize - dataSize; i++)
        block[dataSize + i] = blockSize - dataSize;
        
    return padding;
}

/**
 * calculates the amount of PKCS#5 padding present within a block of data
 *
 * @param block the block of bytes containing padding
 *
 * @return number of trailing bytes in the block that are padding
 */
uint8_t PKCS_5::getPaddingAmount(const uint8_t block[]) const {
    return block[blockSize - 1];
}