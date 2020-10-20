#ifndef MYECB
#define MYECB

#include <istream>
#include <ostream>
#include <cstdint>
#include <new>
#include "ModeOfOperation.hpp"
#include "../ciphers/BlockCipher.hpp"
#include "../padding/BlockPadding.hpp"

class ECB : public BlockModeOfOperation {
private:
    ECB();
    ECB& operator=(const ECB &that) = delete;

public:
    ECB(const BlockCipher &blockCipher, const BlockPadding &blockPadding);
    ECB(const ECB &that);
    ~ECB();

    void encrypt(std::istream &plaintext, std::ostream &ciphertext) const;
    void decrypt(std::istream &ciphertext, std::ostream &plaintext) const;
};

#endif