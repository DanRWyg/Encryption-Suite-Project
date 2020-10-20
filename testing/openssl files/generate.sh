#!/bin/bash

key128=00000000000000000000000000000000
key192=000000000000000000000000000000000000000000000000
key256=0000000000000000000000000000000000000000000000000000000000000000

iv=00000000000000000000000000000000

openssl enc -aes-128-ecb -nosalt -K $key128 -in ../plaintext -out ./ciphertext_aes_128_ecb
openssl enc -aes-192-ecb -nosalt -K $key192 -in ../plaintext -out ./ciphertext_aes_192_ecb
openssl enc -aes-256-ecb -nosalt -K $key256 -in ../plaintext -out ./ciphertext_aes_256_ecb

openssl enc -aes-128-cbc -nosalt -K $key128 -iv $iv -in ../plaintext -out ./ciphertext_aes_128_cbc
openssl enc -aes-192-cbc -nosalt -K $key192 -iv $iv -in ../plaintext -out ./ciphertext_aes_192_cbc
openssl enc -aes-256-cbc -nosalt -K $key256 -iv $iv -in ../plaintext -out ./ciphertext_aes_256_cbc

openssl enc -aes-128-cfb -nosalt -K $key128 -iv $iv -in ../plaintext -out ./ciphertext_aes_128_cfb
openssl enc -aes-192-cfb -nosalt -K $key192 -iv $iv -in ../plaintext -out ./ciphertext_aes_192_cfb
openssl enc -aes-256-cfb -nosalt -K $key256 -iv $iv -in ../plaintext -out ./ciphertext_aes_256_cfb

openssl enc -aes-128-ofb -nosalt -K $key128 -iv $iv -in ../plaintext -out ./ciphertext_aes_128_ofb
openssl enc -aes-192-ofb -nosalt -K $key192 -iv $iv -in ../plaintext -out ./ciphertext_aes_192_ofb
openssl enc -aes-256-ofb -nosalt -K $key256 -iv $iv -in ../plaintext -out ./ciphertext_aes_256_ofb

openssl enc -aes-128-ctr -nosalt -K $key128 -iv $iv -in ../plaintext -out ./ciphertext_aes_128_ctr
openssl enc -aes-192-ctr -nosalt -K $key192 -iv $iv -in ../plaintext -out ./ciphertext_aes_192_ctr
openssl enc -aes-256-ctr -nosalt -K $key256 -iv $iv -in ../plaintext -out ./ciphertext_aes_256_ctr