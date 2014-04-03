#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <des/des.h>
#include <des/hex.h>
#include <des/read.h>
#include <des/convert.h>
#include <des/keygen.h>

// Simple TDES2 CBC encryption example
// Accepts key as command line argument and reads plaintext from stdin
// Prints IV to stderr and ciphertext to stdout

int main(int argc, char** argv){
	char key[TDES2_KEY_SIZE], temp[TDES2_KEY_SIZE*2+1];
	
	// generate key
	keygen(key, TDES2_KEY_SIZE, 1);
	key[TDES2_KEY_SIZE] = 0;
		
	// print out key
	to_hex(key, temp, TDES2_KEY_SIZE, 0);
	printf("%s\n", temp);
		
	return 0;
}
