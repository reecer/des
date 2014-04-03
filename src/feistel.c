#include <string.h>
#include "constants.h"
#include "feistel.h"
#include "xor.h"

void feistel_encrypt(char* input, void (*func)(char*, char*, char*), char subkeys[NUM_ROUNDS][SUBKEY_SIZE], char* dest) {
	int i;
	char L[BLOCK_SIZE/2], R[BLOCK_SIZE/2];
	
	// split plaintext block into halves
	memcpy(L, input, BLOCK_SIZE/2);
	memcpy(R, input + BLOCK_SIZE/2, BLOCK_SIZE/2);
	
	for(i = 0; i < NUM_ROUNDS; i++){
		char subkey[SUBKEY_SIZE], L2[BLOCK_SIZE/2], R2[BLOCK_SIZE/2];
		
		// Use subkey from pre-computed subkeys
		memcpy(subkey, subkeys[i], SUBKEY_SIZE);

		// L[i] = R[i-1]
		memcpy(L2, R, BLOCK_SIZE/2);
		
		// temp = F(R[i-1], K[i])
		func(R, subkey, R2);

		// R[i] = L[i-1] XOR temp
		xor(L, R2, BLOCK_SIZE/2, R);
		
		// update L
		memcpy(L, L2, BLOCK_SIZE/2);
	}

	// C = (R, L)	- had to swap the halves here
	memcpy(dest, R, BLOCK_SIZE/2);
	memcpy(dest + BLOCK_SIZE/2, L, BLOCK_SIZE/2);
	
}
