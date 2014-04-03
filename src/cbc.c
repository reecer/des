#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "cbc.h"
#include "xor.h"

void cbc_encrypt(char* input, char* key, void (*cipher)(char*, char*, char*), char* iv, size_t len, char* dest){
	int i;
	
	char last_block[BLOCK_SIZE];

	// in the first round xor with the iv, in further rounds use the previous block
	memcpy(last_block, iv, BLOCK_SIZE);
	
	for(i = 0; i < len; i+= BLOCK_SIZE){
		char block[BLOCK_SIZE], enc[BLOCK_SIZE];
		int sublen = (i + BLOCK_SIZE > len) ? len - i : BLOCK_SIZE;
		
		if(sublen < BLOCK_SIZE){
			fprintf(stderr, "warning: unpadded block in cbc_encrypt\n");
		}
		
		// copy next block of input
		memcpy(block, &input[i], sublen);

		// xor block with last block
		xor(block, last_block, sublen, block);
		
		// encrypt block
		cipher(block, key, enc);
		
		// update our copy of the previous block
		memcpy(last_block, enc, sublen);
		
		// copy enciphered text to ciphertext array
		memcpy(&dest[i], enc, sublen);
	}
	dest[len] = '\0';
}

void cbc_decrypt(char* input, char* key, void (*cipher)(char*, char*, char*), char* iv, size_t len, char* dest){
	int i;
	char last_block[BLOCK_SIZE];
	
	// in the first round, xor with the iv, in further rounds use the previous block
	memcpy(last_block, iv, BLOCK_SIZE);
	
	for(i = 0; i < len; i+= BLOCK_SIZE){
		char block[BLOCK_SIZE], dec[BLOCK_SIZE];
		int sublen = (i + BLOCK_SIZE > len) ? len - i : BLOCK_SIZE;
		
		if(sublen < BLOCK_SIZE){
			memset(&dest[i], 0, sublen);
			continue;
		}
		
		// copy input block
		memcpy(block, &input[i], sublen);
		
		// decipher
		cipher(block, key, dec);
		
		// xor with the last block (or iv)
		xor(dec, last_block, sublen, dec);
		
		// update our copy of the previous block
		memcpy(last_block, block, sublen);
		
		// copy enciphered text to ciphertext array
		memcpy(&dest[i], dec, sublen);
	}
	dest[len] = '\0';
}
