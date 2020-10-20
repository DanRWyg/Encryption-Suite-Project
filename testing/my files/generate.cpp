#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdint>
#include "../../ciphers/BlockCipher.hpp"
#include "../../ciphers/AES.hpp"
#include "../../padding/BlockPadding.hpp"
#include "../../padding/PKCS_5.hpp"
#include "../../modes/ModeOfOperation.hpp"
#include "../../modes/ECB.hpp"
#include "../../modes/CBC.hpp"
#include "../../modes/CFB.hpp"
#include "../../modes/OFB.hpp"
#include "../../modes/CTR.hpp"

using namespace std;

void encryptFile(ModeOfOperation &moo, const char *plaintextPath, const char *ciphertextPath) {
    ifstream plaintext(plaintextPath);
    ofstream ciphertext(ciphertextPath);

    moo.encrypt(plaintext, ciphertext);    

    plaintext.close();
    ciphertext.close();
}

void decryptFile(ModeOfOperation &moo, const char *ciphertextPath, const char *plaintextPath) {
    ifstream ciphertext(ciphertextPath);
    ofstream plaintext(plaintextPath);

    moo.decrypt(ciphertext, plaintext);    

    ciphertext.close();
    plaintext.close();
}

void generateECB(BlockCipher &bc, BlockPadding &padding, const char *plaintextPath, const char *ciphertextPath, const char *_plaintextPath) {
    ECB ecb(bc, padding);

    encryptFile(ecb, plaintextPath, ciphertextPath);
    decryptFile(ecb, ciphertextPath, _plaintextPath);
}

void generateCBC(BlockCipher &bc, BlockPadding &padding, uint8_t *iv, const char *plaintextPath, const char *ciphertextPath, const char *_plaintextPath) {
    CBC cbc(bc, padding, iv, bc.getBlockSize());

    encryptFile(cbc, plaintextPath, ciphertextPath);
    decryptFile(cbc, ciphertextPath, _plaintextPath);
}

void generateCFB(BlockCipher &bc, uint8_t *iv, const char *plaintextPath, const char *ciphertextPath, const char *_plaintextPath) {
    CFB cfb(bc, iv, bc.getBlockSize());

    encryptFile(cfb, plaintextPath, ciphertextPath);
    decryptFile(cfb, ciphertextPath, _plaintextPath);
}

void generateOFB(BlockCipher &bc, uint8_t *iv, const char *plaintextPath, const char *ciphertextPath, const char *_plaintextPath) {
    OFB ofb(bc, iv, bc.getBlockSize());

    encryptFile(ofb, plaintextPath, ciphertextPath);
    decryptFile(ofb, ciphertextPath, _plaintextPath);
}

void generateCTR(BlockCipher &bc, uint8_t *iv, const char *plaintextPath, const char *ciphertextPath, const char *_plaintextPath) {
    CTR ctr(bc, iv, bc.getBlockSize());

    encryptFile(ctr, plaintextPath, ciphertextPath);
    decryptFile(ctr, ciphertextPath, _plaintextPath);
}

int main() {

    uint8_t key[32] = { 0 };

    cout << fixed << setfill('0') << hex;
    
    cout << "KEY: ";
    for (int i = 0; i < 32; i += 2)
        cout << setw(2) << (int) key[i] << setw(2) << (int) key[i+1] << " ";
    cout << endl;

    uint8_t iv[16] = { 0 };
    cout << "IV:  ";
    for (int i = 0; i < 16; i += 2)
        cout << setw(2) << (int) iv[i] << setw(2) << (int) iv[i+1] << " ";
    cout << endl;

    AES aes128(key, AES::AES128);
    AES aes192(key, AES::AES192);
    AES aes256(key, AES::AES256);

    PKCS_5 padding(16);

    generateECB(aes128, padding, "../plaintext", "./ciphertext_aes_128_ecb", "./plaintext_aes_128_ecb");
    generateECB(aes192, padding, "../plaintext", "./ciphertext_aes_192_ecb", "./plaintext_aes_192_ecb");
    generateECB(aes256, padding, "../plaintext", "./ciphertext_aes_256_ecb", "./plaintext_aes_256_ecb");

    generateCBC(aes128, padding, iv, "../plaintext", "./ciphertext_aes_128_cbc", "./plaintext_aes_128_cbc");
    generateCBC(aes192, padding, iv, "../plaintext", "./ciphertext_aes_192_cbc", "./plaintext_aes_192_cbc");
    generateCBC(aes256, padding, iv, "../plaintext", "./ciphertext_aes_256_cbc", "./plaintext_aes_256_cbc");

    generateCFB(aes128, iv, "../plaintext", "./ciphertext_aes_128_cfb", "./plaintext_aes_128_cfb");
    generateCFB(aes192, iv, "../plaintext", "./ciphertext_aes_192_cfb", "./plaintext_aes_192_cfb");
    generateCFB(aes256, iv, "../plaintext", "./ciphertext_aes_256_cfb", "./plaintext_aes_256_cfb");

    generateOFB(aes128, iv, "../plaintext", "./ciphertext_aes_128_ofb", "./plaintext_aes_128_ofb");
    generateOFB(aes192, iv, "../plaintext", "./ciphertext_aes_192_ofb", "./plaintext_aes_192_ofb");
    generateOFB(aes256, iv, "../plaintext", "./ciphertext_aes_256_ofb", "./plaintext_aes_256_ofb");

    generateCTR(aes128, iv, "../plaintext", "./ciphertext_aes_128_ctr", "./plaintext_aes_128_ctr");
    generateCTR(aes192, iv, "../plaintext", "./ciphertext_aes_192_ctr", "./plaintext_aes_192_ctr");
    generateCTR(aes256, iv, "../plaintext", "./ciphertext_aes_256_ctr", "./plaintext_aes_256_ctr");
}