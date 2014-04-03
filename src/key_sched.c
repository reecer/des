#include "constants.h"
#include "key_sched.h"

// PC-1 table (initial key permutation)
int PC1[KEY_BITS] = {
	57,	49,	41,	33,	25,	17,	9,
	1,	58,	50,	42,	34,	26,	18,
	10,	2,	59,	51,	43,	35,	27,
	19,	11,	3,	60,	52,	44,	36,
	63,	55,	47,	39,	31,	23,	15,
	7,	62,	54,	46,	38,	30,	22,
	14,	6,	61,	53,	45,	37,	29,
	21,	13,	5,	28,	20,	12,	4
};

// PC-2 table (permutation for generating each subkey)
int PC2[SUBKEY_BITS] = {
	14,	17,	11,	24,	1,	5,	3,	28,
	15,	6,	21,	10,	23,	19,	12,	4,
	26,	8,	16,	7,	27,	20,	13,	2,
	41,	52,	31,	37,	47,	55,	30,	40,
	51,	45,	33,	48,	44,	49,	39,	56,
	34,	53,	46,	42,	50,	36,	29,	32
};

int HALF_BITS = KEY_BITS / 2;

void key_sched(char* key, char dest[NUM_ROUNDS][SUBKEY_SIZE]){
    int i;
    char k[KEY_BITS];
        
    // Apply PC-1
    // i figured we should map bits as bytes so it is easier to address them in the shifts and PC-2
    for(i = 0; i < KEY_BITS; i++){
    	int byte_index = (PC1[i]-1) / 8;
    	int bit_offset = 7 - ((PC1[i]-1) % 8);
    	k[i] = (key[byte_index] & (1 << bit_offset)) ? 1 : 0;
    }

    for(i = 0; i < NUM_ROUNDS; i++){
        // no need to split key block into halves because we can just do pointer arithmetic when we shift
        
        // shift once
        rotate_array(k, HALF_BITS);
        rotate_array(k + HALF_BITS, HALF_BITS);       

        // shift twice in all rounds except 1,2,9,16
        if(! (i == 0 || i == 1 || i == 8 || i == 15)){
	        rotate_array(k, HALF_BITS);
	        rotate_array(k + HALF_BITS, HALF_BITS);
        }
        
        // copy key and apply PC-2 to it, saving as subkey
        // first zero out subkey so we can do bit manipulation without worrying about garbage
		int j;
		for(j = 0; j < SUBKEY_SIZE; j++)
			dest[i][j] = 0;
		// copy bits into subkey using PC-2 mapping (using real bits again instead of bytes)
		for(j = 0; j < SUBKEY_BITS; j++){
			int byte_index = j / 8;
			int bit_offset = 7 - (j % 8);
			dest[i][byte_index] = dest[i][byte_index] | (k[PC2[j]-1] << bit_offset);
		}
        
    }   
}

// needed to add the length param, renamed it as well
void rotate_array(char* arr, int len){
    int temp = arr[0], i;
    for(i = 0; i < len - 1; i++){
    	arr[i] = arr[i+1];
    }
    arr[i] = temp;
}
