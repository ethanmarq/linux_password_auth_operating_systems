// gcc asg1.c -o asg1 -lcrypto -lpthread
// ./asg dicitonary_file hash_file

#include <stdio.h>
#include <openssl/sha.h> // Include for SHA512 functions

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

char word[SHA512_DIGEST_LENGTH];
const char *hash_file;

void * threadAFunc(){
  printf("\nThread1 with tid %lu\n", (unsigned long)pthread_self());

  printf("\tPlease enter your password: > ");
  scanf("%s", word);

  return NULL;
}

void * threadBFunc(){

  printf("\nThread2 with tid %lu\n", (unsigned long)pthread_self());

  unsigned char digest[SHA512_DIGEST_LENGTH];
  SHA512((const unsigned char *)word,
            strlen(word), digest);

  int found = 0;
  char hex[200];

  char test_word[200];
  char test_hash[SHA512_DIGEST_LENGTH*2+1];

  for (int i = 0; i < SHA512_DIGEST_LENGTH; i++){
    sprintf(&hex[i * 2], "%02x", digest[i]);
  }

  hex[SHA512_DIGEST_LENGTH*2] = '\0';

  FILE *hfile = fopen(hash_file, "r");
  while (fscanf(hfile, "%s %s", test_word, test_hash) != EOF){
    if(strcmp(hex, test_hash) == 0){
      found++;
    break;
    }

  fclose(hfile);

  char *hash_copy = malloc(SHA512_DIGEST_LENGTH*2+1);
  if (hash_copy == NULL){
    printf("malloc failed\n");
    return NULL;
  }
  strcpy(hash_copy, hex);

  return (void *)hash_copy;
  }


  if (found){
    printf("\tThis is a weak password, please change your password.\n");
  } else {
    printf("\tPassword was not found in the hash table.\n");
    printf("\tThis is a strong password, good job!!!\n");
  }

  fclose(hfile);
  return NULL;
  }

int main(int argc, char *argv[]) {
    if (argc < 3){
      printf("Invalid usage: ./hash512 dictionary_file hash_file");
      return 1;
    }

    char *dict_file = argv[1];
    hash_file = argv[2];

    pid_t pid = fork();

    if (pid < 0){
      printf("no fork");
      return 1;
    }

    if (pid == 0){
      execl("./hash512", "./hash512", dict_file, hash_file, NULL);
      printf("no exec");
      exit(1);
    }

    int status;
    waitpid(pid, &status, 0);

    pthread_t threadIdA, threadIdB;
    int err;

    err = pthread_create(&threadIdA, NULL, threadAFunc, NULL);

    if (err){
      printf("Thread failed\n");
      return err;
    }

    err = pthread_join(threadIdA, NULL);
    if (err){
      printf( "Failed thread join: %d\n", err);
      return err;
    }

    err = pthread_create(&threadIdB, NULL, threadBFunc, NULL);
    if (err){
      printf("Thread failed\n");
      return err;
    }

    void *ret;
    err = pthread_join(threadIdB, &ret);
    if (err){
      printf( "Failed thread join: %d\n", err);
      return err;
    }

    if (ret != NULL){
      char *hash = (char *)ret;
  printf("\tPassword is: %s\n", word);
      printf("\tPassword hash is: %s\n", hash);
      free(hash);
    }

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

{4}. Now create a second thread that executes a function to test user’s password.
This function will create a hash of the stored password and search the hash_file to
see if that hash is found. If it is found, the
password was weak, otherwise praise the user for using a strong password.
 */
