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
	size_t input_len;
	char iv[DES_BLOCK_SIZE + 1], key[TDES2_KEY_SIZE], temp[DES_BLOCK_SIZE*2+1];
	char *stdin_buffer = 0, *stdout_buffer = 0;
	
	// check that the key was provided
	if(argc != 2){
		fprintf(stderr, "error: must provide hexadecimal key (and nothing else) as command line argument\n");
		exit(1);
	}
	
	// check that the key is the right length
	if(strlen(argv[1]) != TDES2_KEY_SIZE*2){
		fprintf(stderr, "error: expected %d bytes for key\n", TDES2_KEY_SIZE);
	}
	
	// convert key
	from_hex(argv[1], key, TDES2_KEY_SIZE);
	
	// generate iv
	keygen(iv, DES_BLOCK_SIZE, 0);
	iv[DES_BLOCK_SIZE] = 0;
		
	// read and pad input
	stdin_buffer = read_stdin(&input_len);
	stdin_buffer = convert_from(stdin_buffer, "raw", &input_len);

	// alloc space for output
	stdout_buffer = malloc(sizeof(char)*(input_len+1));
		
	// perform encryption
	des_encrypt_cbc(stdin_buffer, key, iv, input_len, stdout_buffer);
		
	// print out iv
	to_hex(iv, temp, DES_BLOCK_SIZE, 0);
	fprintf(stderr, "IV: %s\n\n", temp);
		
	// print out ciphertext
	stdout_buffer = convert_to(stdout_buffer, "hex", &input_len);
	fwrite(stdout_buffer, sizeof(char), input_len, stdout);
	
	printf("\n");
	
	// clean up
	free(stdin_buffer);
	free(stdout_buffer);	

	return 0;
}
