#ifndef ip_fp_h
#define ip_fp_h

/**
initial_permutation:
  Applies the DES algorithm's Initial Permutation (IP) block to the input and stores the result in output.
*/

void initial_permutation(char* input, char* output);

/**
final_permutation:
  Applies the DES algorithm's Final Permutation (FP) block to the input and stores the result in output.
*/
void final_permutation(char* input, char* output);

#endif
