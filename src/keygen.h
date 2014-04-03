#ifndef keygen_h
#define keygen_h

/**
keygen:
 Generates a key of the specified length in 'bytes' and stores it to 'buf'.
 If the 'key' flag true, only the upper 7 bits of each byte will be used,
 as in a DES key, and /dev/random will be used instead of /dev/urandom.
*/
void keygen(char* buf, int bytes, int key);

/**
rand_byte:
 Returns one random byte acquired from /dev/random (if sec is true) or /dev/urandom
*/
char rand_byte(int sec);

#endif
