#ifndef cbc_h
#define cbc_h

/**
cbc_encrypt:
  Takes a char array 'input' and processes it with the given 'cipher' function
  using CBC mode and the given initialization vector 'iv'. Writes a char array
  consisting of the concatenation of the blocks generated by using CBC with the
  given cipher into the location given by 'dest'.
  
  The parameters of 'cipher' are (input, key, output)
*/
void cbc_encrypt(char* input, char* key, void (*cipher)(char*, char*, char*), char* iv, size_t len, char* dest);

/**
cbc_decrypt:
  Decrypts the input in CBC mode using given cipher, key and IV. Stores the plaintext in dest.
*/
void cbc_decrypt(char* input, char* key, void (*cipher)(char*, char*, char*), char* iv, size_t len, char* dest);

#endif
