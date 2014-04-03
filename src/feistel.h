#ifndef feistel_h
#define feistel_h

/**
feistel_encrypt:
  Encrypts the 'input' block using round function 'func' and given set of 'subkeys' and stores the result in 'dest'.
  Initial and final permutations are computed using 'ip' and 'fp'.
  
  The parameters of 'func' are (R-input, subkey, output).
*/
void feistel_encrypt(char* input, void (*func)(char*, char*, char*), char subkeys[NUM_ROUNDS][SUBKEY_SIZE], char* dest);

#endif
