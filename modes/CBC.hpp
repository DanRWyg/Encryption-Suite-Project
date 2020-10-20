#ifndef MYCBC
#define MYCBC

#include <istream>
#include <ostream>
#include <cstdint>
#include <new>
#include <stdexcept>
#include "ModeOfOperation.hpp"
#include "../ciphers/BlockCipher.hpp"
#include "../padding/BlockPadding.hpp"

class CBC : public BlockModeOfOperation {
private:
    uint8_t iv[256];
    uint8_t ivSize;

    CBC();
    CBC& operator=(const CBC &that) = delete;

public:
    CBC(const BlockCipher &blockCipher, const BlockPadding &blockPadding, const uint8_t iv[], uint8_t ivSize);
    CBC(const CBC &that);
    ~CBC();

    void encrypt(std::istream &plaintext, std::ostream &ciphertext) const;
    void decrypt(std::istream &ciphertext, std::ostream &plaintext) const;
};

#endif