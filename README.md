# Encryption Suite Project:
### Motivation:
I am always interested in learning how computing systems work. 
Learning about networking (namely, the internet) pointed me towards how frequently encryption is used in our daily lives to access the world wide web.
Thus, I decided I would better understand the modern standards of encryption.
What better way to accomplish this goal than to implement it in the form of a small library API?

### Implementation:
To get a good foundation for this project, I will implementing:
* AES block cipher (128, 192, and 256 bit implementation)
* Several common modes of operation: ECB, CBC, CFB, OBF, and CTR


### Structure:
Before writing code, it is good to think on the _structure_.
Below is a simple UML diagram representing class relationships and important members/methods.
![UML](/project%20resources/UML.png)

### Testing:
So far, extensive tests for the potentially small errors present in the project have not been created.
There is, however, a test to check the validity of my implementation for these algorithms.
1. The [my\ files/compile.sh](/testing/my%20files/compile.sh) bash script will compile the library alongside the program [generate.cpp](/testing/my%20files/generate.cpp).
2. Once run, generate.out will use my library to encrypt [plaintext](/testing/plaintext) into ciphertext files and decrypt those resulting ciphertext files back into plaintext files.
3. The [openssl\ files/compile.sh](/testing/openssl%20files/compile.sh) bash script will also encrypt [plaintext](/testing/plaintext) using openssl.
4. The output of my implementation can be checked against the output of openssl with the [verify.sh](/testing/verify.sh) bash script.


### Sources:
Learning the nitty gritty details of AES was not easy.
Fortunately, there are many resources online.
The primary one I used was [this](https://www.samiam.org/rijndael.html).
If you are interested in making your own implementation of AES, I highly recommend taking a look at it.

I also heavily relied on wikipedia's [page on modes of operation](https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation).
It offers great diagrams describing the various common modes of operation used with block ciphers.
