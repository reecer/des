#ifndef des_round_h
#define des_round_h

/**
  des_round:
    Applies the DES round function to the input using the given subkey, and saves
    the result in the output buffer.
*/
void des_round(char* input, char* subkey, char* output);

#endif
