#include "des_wrapper.h"
#include "constants.h"
#include "feistel.h"
#include "des_round.h"
#include "key_sched.h"
#include "ip_fp.h"
#include "hex.h"
#include "cbc.h"

#include <stdio.h>
#include <string.h>

void des_encrypt(char* input, char* key, char* output){
	char subkeys[NUM_ROUNDS][SUBKEY_SIZE], temp[BLOCK_SIZE], temp2[BLOCK_SIZE];
	
	key_sched(key, subkeys);
	initial_permutation(input, temp);
	feistel_encrypt(temp, des_round, subkeys, temp2);
	final_permutation(temp2, output);
}


void des_decrypt(char* input, char* key, char* output){
	char subkeys[NUM_ROUNDS][SUBKEY_SIZE], temp[BLOCK_SIZE], temp2[BLOCK_SIZE];
	char rev_subkeys[NUM_ROUNDS][SUBKEY_SIZE];
	int i, j;
	
	key_sched(key, subkeys);

	for(i = 0, j = NUM_ROUNDS - 1; i < NUM_ROUNDS; i++, j--){
		memcpy(rev_subkeys[j], subkeys[i], SUBKEY_SIZE);
	}
	
	initial_permutation(input, temp);
	feistel_encrypt(temp, des_round, rev_subkeys, temp2);
	final_permutation(temp2, output);
	
}


void des_encrypt_cbc(char* input, char* key, char* iv, size_t len, char* output){
	cbc_encrypt(input, key, des_encrypt, iv, len, output);
}

void des_decrypt_cbc(char* input, char* key, char* iv, size_t len, char* output){
	cbc_decrypt(input, key, des_decrypt, iv, len, output);
}


void tdes2_encrypt(char* input, char* key, char* output){
	char temp[BLOCK_SIZE], temp2[BLOCK_SIZE], k1[KEY_SIZE], k2[KEY_SIZE];
	memcpy(k1, key, KEY_SIZE);
	memcpy(k2, key+KEY_SIZE, KEY_SIZE);
	des_encrypt(input, k1, temp);
	des_decrypt(temp, k2, temp2);
	des_encrypt(temp2, k1, output);
}

void tdes2_decrypt(char* input, char* key, char* output){
	char temp[BLOCK_SIZE], temp2[BLOCK_SIZE], k1[KEY_SIZE], k2[KEY_SIZE];
	memcpy(k1, key, KEY_SIZE);
	memcpy(k2, key+KEY_SIZE, KEY_SIZE);
	des_decrypt(input, k1, temp);
	des_encrypt(temp, k2, temp2);
	des_decrypt(temp2, k1, output);
}

void tdes2_encrypt_cbc(char* input, char* key, char* iv, size_t len, char* output){
	cbc_encrypt(input, key, tdes2_encrypt, iv, len, output);
}

void tdes2_decrypt_cbc(char* input, char* key, char* iv, size_t len, char* output){
	cbc_decrypt(input, key, tdes2_decrypt, iv, len, output);
}

void tdes3_encrypt(char* input, char* key, char* output){
	char temp[BLOCK_SIZE], temp2[BLOCK_SIZE], k1[KEY_SIZE], k2[KEY_SIZE], k3[KEY_SIZE];
	memcpy(k1, key, KEY_SIZE);
	memcpy(k2, key+KEY_SIZE, KEY_SIZE);
	memcpy(k3, key+2*KEY_SIZE, KEY_SIZE);
	des_encrypt(input, k1, temp);
	des_decrypt(temp, k2, temp2);
	des_encrypt(temp2, k3, output);
}

void tdes3_decrypt(char* input, char* key, char* output){
	char temp[BLOCK_SIZE], temp2[BLOCK_SIZE], k1[KEY_SIZE], k2[KEY_SIZE], k3[KEY_SIZE];
	memcpy(k1, key, KEY_SIZE);
	memcpy(k2, key+KEY_SIZE, KEY_SIZE);
	memcpy(k3, key+2*KEY_SIZE, KEY_SIZE);
	des_decrypt(input, k3, temp);
	des_encrypt(temp, k2, temp2);
	des_decrypt(temp2, k1, output);
}

void tdes3_encrypt_cbc(char* input, char* key, char* iv, size_t len, char* output){
	cbc_encrypt(input, key, tdes3_encrypt, iv, len, output);
}

void tdes3_decrypt_cbc(char* input, char* key, char* iv, size_t len, char* output){
	cbc_decrypt(input, key, tdes3_decrypt, iv, len, output);
}
