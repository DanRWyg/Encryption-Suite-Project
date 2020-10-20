#ifndef MYMODEOFOPERATION
#define MYMODEOFOPERATION

#include <istream>
#include <ostream>
#include <cstdlib>
#include <stdexcept>
#include "../ciphers/BlockCipher.hpp"
#include "../padding/BlockPadding.hpp"

class ModeOfOperation {
private:
    ModeOfOperation();
    ModeOfOperation(const ModeOfOperation &that) = delete;
    ModeOfOperation& operator=(const ModeOfOperation &that) = delete;

protected:
    const BlockCipher &blockCipher;
    ModeOfOperation(const BlockCipher &blockCipher);

public:
    virtual ~ModeOfOperation();
    virtual void encrypt(std::istream &plaintext, std::ostream &ciphertext) const = 0;
    virtual void decrypt(std::istream &ciphertext, std::ostream &plaintext) const = 0;
};

class BlockModeOfOperation : public ModeOfOperation {
private:
    BlockModeOfOperation();
    BlockModeOfOperation(const BlockModeOfOperation &that) = delete;
    BlockModeOfOperation& operator=(const BlockModeOfOperation &that) = delete;

protected:
    const BlockPadding &blockPadding;
    BlockModeOfOperation(const BlockCipher &blockCipher, const BlockPadding &blockPadding);

public:
    virtual ~BlockModeOfOperation();
};

class StreamModeOfOperation : public ModeOfOperation {
private:
    StreamModeOfOperation();
    StreamModeOfOperation(const StreamModeOfOperation &that) = delete;
    BlockModeOfOperation& operator=(const StreamModeOfOperation &that) = delete;

protected:
    StreamModeOfOperation(const BlockCipher &blockCipher);

public:
    virtual ~StreamModeOfOperation();
};

#endif