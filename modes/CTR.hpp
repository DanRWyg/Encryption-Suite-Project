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