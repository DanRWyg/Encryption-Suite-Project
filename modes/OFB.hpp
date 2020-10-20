#ifndef MYOFB
#define MYOFB

#include <istream>
#include <ostream>
#include <cstdint>
#include <new>
#include <stdexcept>
#include "ModeOfOperation.hpp"
#include "../ciphers/BlockCipher.hpp"
#include "../padding/BlockPadding.hpp"

class OFB : public StreamModeOfOperation {
private:
    uint8_t iv[256];
    uint8_t ivSize;

    OFB();
    OFB& operator=(const OFB &that) = delete;

public:
    OFB(const BlockCipher &blockCipher, const uint8_t iv[], uint8_t ivSize);
    OFB(const OFB &that);
    ~OFB();

    void encrypt(std::istream &plaintext, std::ostream &ciphertext) const;
    void decrypt(std::istream &ciphertext, std::ostream &plaintext) const;
};

#endif