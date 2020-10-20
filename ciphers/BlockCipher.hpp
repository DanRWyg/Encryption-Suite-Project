/**
 * header file for the abstract block cipher superclass.
 * @file BlockCipher.hpp
 * @author Daniel Wygant
 * @version 1.0 10/20/2020
 */


#ifndef MYBLOCKCIPHER
#define MYBLOCKCIPHER

#include <cstdint>
#include <stdexcept>

class BlockCipher {
private:
    BlockCipher();
    BlockCipher(const BlockCipher &blockCipher) = delete;
    BlockCipher& operator=(const BlockCipher &that) = delete;

protected:
    const uint8_t blockSize;
    BlockCipher(uint8_t blockSize);
    
public:
    virtual ~BlockCipher();
    virtual void encryptBlock(const uint8_t plaintext[], uint8_t ciphertext[]) const = 0;
    virtual void decryptBlock(const uint8_t ciphertext[], uint8_t plaintext[]) const = 0;
    uint8_t getBlockSize() const;
};

#endif