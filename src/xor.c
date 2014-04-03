#include <stdlib.h>
#include "constants.h"
#include "xor.h"

void xor(char* a, char* b, int len, char* dest){
	int i;
	for(i = 0; i < len; i++)
		dest[i] = a[i] ^ b[i];
}
