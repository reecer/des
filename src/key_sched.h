#ifndef key_sched_h
#define key_sched_h

/**
 * key_sched:
 * 	Generates a key schedule (subkeys) from 'key'. The results
 * 	are stored in 'dest' array.
 */
void key_sched(char key[KEY_SIZE], char dest[NUM_ROUNDS][SUBKEY_SIZE]);

/**
 * Perform a left cyclic shift on 'arr'
 */
void rotate_array(char* arr, int len);

#endif
