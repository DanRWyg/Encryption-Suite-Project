/**
 * header file for the CTR mode of operation.
 * @file CTR.hpp
 * @author Daniel Wygant
 * @version 1.0 10/20/2020
 */

#ifndef MYCTR
#define MYCTR

#include <istream>
#include <ostream>
#include <cstdint>
#include <new>
#include "ModeOfOperation.hpp"
#include "../ciphers/BlockCipher.hpp"
#include "../padding/BlockPadding.hpp"

class CTR : public StreamModeOfOperation {
private:
    uint8_t iv[256];
    uint8_t ivSize;
    
    CTR();
    CTR& operator=(const CTR &that) = delete;

public:
    CTR(const BlockCipher &blockCipher, const uint8_t iv[], uint8_t ivSize);
    CTR(const CTR &that);
    ~CTR();

    void encrypt(std::istream &plaintext, std::ostream &ciphertext) const;
    void decrypt(std::istream &ciphertext, std::ostream &plaintext) const;
};

#endif