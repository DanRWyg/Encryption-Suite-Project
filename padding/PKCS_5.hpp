/**
 * header file for the PKCS#5 block padding standard.
 * @file PKCS_5.hpp
 * @author Daniel Wygant
 * @version 1.0 10/20/2020
 */

#ifndef MYPKCS_5
#define MYPKCS_5

#include <cstdint>
#include <new>
#include "BlockPadding.hpp"

class PKCS_5 : public BlockPadding {
private:
    PKCS_5();
    PKCS_5& operator=(const PKCS_5 &that) = delete;

public:
    PKCS_5(uint8_t blockSize);
    PKCS_5(const PKCS_5 &that);
    ~PKCS_5();

    uint8_t* addPadding(uint8_t block[], uint8_t dataSize) const;
    uint8_t getPaddingAmount(const uint8_t block[]) const;
};

#endif