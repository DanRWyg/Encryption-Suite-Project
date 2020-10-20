#ifndef MYBLOCKPADDING
#define MYBLOCKPADDING

#include <cstdint>
#include <stdexcept>

class BlockPadding {
private:
    BlockPadding();
    BlockPadding(const BlockPadding &that) = delete;
    BlockPadding& operator=(const BlockPadding &that) = delete;

protected:
    const uint8_t blockSize;
    BlockPadding(uint8_t blockSize);

public:
    virtual ~BlockPadding();
    virtual uint8_t* addPadding(uint8_t block[], uint8_t dataSize) const = 0;
    virtual uint8_t getPaddingAmount(const uint8_t block[]) const = 0;
    uint8_t getBlockSize() const;
};

#endif