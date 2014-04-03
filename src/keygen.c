#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "keygen.h"

char rand_byte(int sec){
	char c = 0;
	int rh = open(sec?"/dev/random":"/dev/urandom", O_RDONLY);
    if(read(rh, &c, sizeof(char)) < 0){
       	fprintf(stderr, "unable to acquire random data from /dev/random\n");
       	exit(EXIT_FAILURE);
   	}
	close(rh);
	return c;
}

void keygen(char* buf, int bytes, int key){
	int i;
	char mask = key?0xFE:0xFF;
	for(i = 0; i < bytes; i++)
		buf[i] = rand_byte(key) & mask;
	// TODO: calculate parity bit (if we feel like implementing it)
	buf[i] = '\0';
}
