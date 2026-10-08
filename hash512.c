// gcc hash512.c -o hash512 -lcrypto
// ./hash512 dictionary_file hash_file

#include <stdio.h>
#include <string.h>
#include <openssl/sha.h> // Include for SHA512 functions

int main() {
    const char *string_to_hash = "cactus";
    unsigned char digest[SHA512_DIGEST_LENGTH];
    // this is a macro defined in the header file
    // in  /usr/include/openssl/sha.h circa line 85.
    // Open that file and check it out.
    // the terms digest and hash value are synonyms

    // Calculate the SHA512 hash
    SHA512((const unsigned char *)string_to_hash,
                strlen(string_to_hash), digest);

    // Print the hash in hex format, every byte as 2 hex digits
    // so you will see 128 characters printed, 64*2

    printf("Length of the hash: %d\n", SHA512_DIGEST_LENGTH);
    printf("SHA512 hash of \"%s\": ", string_to_hash);
    for (int i = 0; i < SHA512_DIGEST_LENGTH; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");


    printf("Hash file was successfully created.");

    return 0;
}
/*
1. Write a small program that generates SHA512 hashes for every word in the
provided dictionary_file. This dictionary file will be passed as the first command line
argument (CLA) to this program. Name your source code hash512.c, your
executable hash512, include <openssl/sha.h> header file and compile with -lcrypto.
- grab three input arguments

- open hash.txt
- open dict.txt
 - read each word
 - loop over each word, generate hash
 - save word hash\n
-


**Please note that you are not implementing the hashing algorithm itself, you are
simply calling the C function that calculates the SHA512 hash. You will be using the
newer version 3 openssl functions residing in the sha.h header file. To accomplish
this on the SoC machine you will need to include openssl/sha.h header file, and
compile with -lcrypto. If ssl library is not installed on your vm, you can install it with
command sudo apt install libssl-dev
 */
