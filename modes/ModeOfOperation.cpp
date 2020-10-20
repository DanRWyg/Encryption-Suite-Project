/**
 * class implementations for the abstract mode of operations superclasses.
 * @file ModeOfOperation.cpp
 * @author Daniel Wygant
 * @version 1.0 10/20/2020
 */

#include "ModeOfOperation.hpp"

/**
 * ModeOfOperation primary constructor
 *
 * @param blockCipher a reference to a BlockCipher that will be used to encrypt/decrypt data
 */
ModeOfOperation::ModeOfOperation(const BlockCipher &blockCipher) : blockCipher(blockCipher) {

}

/**
 * ModeOfOperation destructor
 */
ModeOfOperation::~ModeOfOperation() {
    
}

/**
 * BlockModeOfOperation primary constructor
 *
 * @param blockCipher a reference to a BlockCipher that will be used to encrypt/decrypt data
 * @param blockPadding the block padding method to be used to manage padding the data to be encrypted/decrypted
 * 
 * @throws std::invalid_argument if blockCipher and blockPadding don't have the same blockSize
 */
BlockModeOfOperation::BlockModeOfOperation(const BlockCipher &blockCipher, const BlockPadding &blockPadding) : ModeOfOperation(blockCipher), blockPadding(blockPadding) {
    if (blockCipher.getBlockSize() != blockPadding.getBlockSize())
        throw std::invalid_argument("blockCipher and blockPadding must have the same blockSize");
}

/**
 * BlockModeOfOperation destructor
 */
BlockModeOfOperation::~BlockModeOfOperation() {
    
}

/**
 * StreamModeOfOperation primary constructor
 *
 * @param blockCipher a reference to a BlockCipher that will be used to encrypt/decrypt data
 */
StreamModeOfOperation::StreamModeOfOperation(const BlockCipher &blockCipher) : ModeOfOperation(blockCipher) {

}

/**
 * StreamModeOfOperation destructor
 */
StreamModeOfOperation::~StreamModeOfOperation() {
    
}