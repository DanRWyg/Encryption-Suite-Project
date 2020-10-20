#!/bin/bash

diff ./my\ files/ciphertext_aes_128_ecb ./openssl\ files/ciphertext_aes_128_ecb -q
diff ./my\ files/ciphertext_aes_192_ecb ./openssl\ files/ciphertext_aes_192_ecb -q
diff ./my\ files/ciphertext_aes_256_ecb ./openssl\ files/ciphertext_aes_256_ecb -q

diff ./my\ files/plaintext_aes_128_ecb ./plaintext -q
diff ./my\ files/plaintext_aes_192_ecb ./plaintext -q
diff ./my\ files/plaintext_aes_256_ecb ./plaintext -q


diff ./my\ files/ciphertext_aes_128_cbc ./openssl\ files/ciphertext_aes_128_cbc -q
diff ./my\ files/ciphertext_aes_192_cbc ./openssl\ files/ciphertext_aes_192_cbc -q
diff ./my\ files/ciphertext_aes_256_cbc ./openssl\ files/ciphertext_aes_256_cbc -q

diff ./my\ files/plaintext_aes_128_cbc ./plaintext -q
diff ./my\ files/plaintext_aes_192_cbc ./plaintext -q
diff ./my\ files/plaintext_aes_256_cbc ./plaintext -q


diff ./my\ files/ciphertext_aes_128_cfb ./openssl\ files/ciphertext_aes_128_cfb -q
diff ./my\ files/ciphertext_aes_192_cfb ./openssl\ files/ciphertext_aes_192_cfb -q
diff ./my\ files/ciphertext_aes_256_cfb ./openssl\ files/ciphertext_aes_256_cfb -q

diff ./my\ files/plaintext_aes_128_cfb ./plaintext -q
diff ./my\ files/plaintext_aes_192_cfb ./plaintext -q
diff ./my\ files/plaintext_aes_256_cfb ./plaintext -q


diff ./my\ files/ciphertext_aes_128_ofb ./openssl\ files/ciphertext_aes_128_ofb -q
diff ./my\ files/ciphertext_aes_192_ofb ./openssl\ files/ciphertext_aes_192_ofb -q
diff ./my\ files/ciphertext_aes_256_ofb ./openssl\ files/ciphertext_aes_256_ofb -q

diff ./my\ files/plaintext_aes_128_ofb ./plaintext -q
diff ./my\ files/plaintext_aes_192_ofb ./plaintext -q
diff ./my\ files/plaintext_aes_256_ofb ./plaintext -q


diff ./my\ files/ciphertext_aes_128_ctr ./openssl\ files/ciphertext_aes_128_ctr -q
diff ./my\ files/ciphertext_aes_192_ctr ./openssl\ files/ciphertext_aes_192_ctr -q
diff ./my\ files/ciphertext_aes_256_ctr ./openssl\ files/ciphertext_aes_256_ctr -q

diff ./my\ files/plaintext_aes_128_ctr ./plaintext -q
diff ./my\ files/plaintext_aes_192_ctr ./plaintext -q
diff ./my\ files/plaintext_aes_256_ctr ./plaintext -q