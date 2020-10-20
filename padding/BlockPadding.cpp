/**
 * class implementation for the abstract block padding superclass.
 * @file BlockPadding.cpp
 * @author Daniel Wygant
 * @version 1.0 10/20/2020
 */

#include "BlockPadding.hpp"

/**
 * BlockPadding primary constructor
 *
 * @param blockSize the size in bytes used to calculate the appropriate amount of padding
 *
 * @throws std::out_of_range if blockSize is 0
 */
BlockPadding::BlockPadding(uint8_t blockSize) : blockSize(blockSize) {
    if (blockSize == 0)
        throw std::out_of_range("blockSize must be greater than 0");
}

/**
 * BlockPadding destructor 
 */
BlockPadding::~BlockPadding() {

}

/**
 * @return [BlockPadding::blockSize]
 */
uint8_t BlockPadding::getBlockSize() const {
    return blockSize;
}