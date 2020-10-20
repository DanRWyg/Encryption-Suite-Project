#ifndef MYCFB
#define MYCFB

#include <istream>
#include <ostream>
#include <cstdint>
#include <new>
#include <stdexcept>
#include "ModeOfOperation.hpp"
#include "../ciphers/BlockCipher.hpp"
#include "../padding/BlockPadding.hpp"

class CFB : public StreamModeOfOperation {
private:
    uint8_t iv[256];
    uint8_t ivSize;

    CFB();
    CFB& operator=(const CFB &that) = delete;

public:
    CFB(const BlockCipher &blockCipher, const uint8_t iv[], uint8_t ivSize);
    CFB(const CFB &that);
    ~CFB();

    void encrypt(std::istream &plaintext, std::ostream &ciphertext) const;
    void decrypt(std::istream &ciphertext, std::ostream &plaintext) const;
};

#endif