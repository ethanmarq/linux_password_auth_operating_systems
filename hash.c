// gcc hash.c -o asg1 -lcrypto -lpthread
// ./asg

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

    // printf("Thread1 with tid %ld", );
    // printf("Please enter your password: >")
    // printf("Thread2 with tid %ld", );
    // printf("Password hash is: ", );
    // printf("Password is: ", );
    // printf("This is a weak password, please change your password.");
    // printf("This is a strong password, good job!!!");
    // printf("Password was not found in the hash table.");

    return 0;
}

/*
1. Now write another program that will test if user has a strong password. You need
to ask user for his password, create a hash of the password, and then compare it to
the hashes in the hash_file. If found, the password was a dictionary word and is,
therefore, weak, otherwise the password is strong. Name your file asg1.c, and
name the binary asg1. This program will take dictionary_file as the first CLA, and
hash_file as the second CLA.

2. In main create a child process and tell it to execute your ./hash512 binary,
passing with the dictionary _file to execute via an exec call. (This creates your
hash_file by executing the program you wrote in Part1) This file must exist before
attempting to read from it.

3. Now parent creates a thread that asks user for a password and stores it in some
global variable.

4. Now create a second thread that executes a function to test user’s password.
This function will create a hash of the stored password and search the hash_file to
see if that hash is found. If it is found, the
password was weak, otherwise praise the user for using a strong password.
 */
