#ifndef des_wrapper_h
#define des_wrapper_h

#include <string.h>

// Definitions of block/key sizes in bytes
#define DES_BLOCK_SIZE 8
#define DES_KEY_SIZE 8
#define TDES2_KEY_SIZE 16
#define TDES3_KEY_SIZE 24

/**
  des_encrypt:
    Wrapper for combining IP, key schedule, Feistel algorithm, and FP for DES encryption (one block)
*/
void des_encrypt(char* input, char* key, char* output);

/**
  des_decrypt:
    Wrapper for combining IP, key schedule, Feistel algorithm, and FP for DES decryption (one block)
*/
void des_decrypt(char* input, char* key, char* output);

/**
  tdes2_encrypt:
    Wrapper implementing triple-DES
    Key size is 16 bytes
*/
void tdes2_encrypt(char* input, char* key, char* output);

/**
  tdes2_decrypt:
    Wrapper implementing triple-DES
*/
void tdes2_decrypt(char* input, char* key, char* output);

/**
  des_encrypt_cbc:
    Wrapper for DES CBC encryption of input of arbitrary length
*/
void des_encrypt_cbc(char* input, char* key, char* iv, size_t len, char* output);

/**
  des_decrypt_cbc:
    Wrapper for DES CBC encryption of input of arbitrary length
*/
void des_decrypt_cbc(char* input, char* key, char* iv, size_t len, char* output);

/**
  tdes2_encrypt_cbc:
    Wrapper for 3DES CBC encryption of input of arbitrary length
*/
void tdes2_encrypt_cbc(char* input, char* key, char* iv, size_t len, char* output);

/**
  tdes2_decrypt_cbc:
    Wrapper for 3DES CBC encryption of input of arbitrary length
*/
void tdes2_decrypt_cbc(char* input, char* key, char* iv, size_t len, char* output);

#endif
