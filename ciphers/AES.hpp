#ifndef MYAES
#define MYAES
#include <cstdint>
#include "BlockCipher.hpp"

class AES : public BlockCipher {
private:
    AES();
    AES& operator=(const AES &that) = delete;

public:
    enum KEY_SIZE : uint8_t { AES128 = 16, AES192 = 24, AES256 = 32 };

    AES(const uint8_t key[], KEY_SIZE keySize = AES128);
    AES(const AES &that);
    ~AES();

    void encryptBlock(const uint8_t plaintext[], uint8_t ciphertext[]) const;
    void decryptBlock(const uint8_t ciphertext[], uint8_t plaintext[]) const;

private:
    const static uint8_t RCON_TABLE[];
    const static uint8_t EXP_TABLE[];
    const static uint8_t LOG_TABLE[];
    const static uint8_t SBOX_TABLE[];
    const static uint8_t SBOX_INV_TABLE[];

    uint8_t key[32];
    KEY_SIZE keySize;
    uint8_t ekey[240];

    void generateExpandedKey();

    void addRoundKey(uint8_t block[4][4], int round) const;
    static void sboxSub(uint8_t block[4][4]);
    static void sboxSubInv(uint8_t block[4][4]);
    static void shiftRows(uint8_t block[4][4]);
    static void shiftRowsInv(uint8_t block[4][4]);
    static void mixColumns(uint8_t block[4][4]);
    static void mixColumnsInv(uint8_t block[4][4]);
    static uint8_t multiplyGF(uint8_t a, uint8_t b);
};

#endif