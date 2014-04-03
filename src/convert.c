#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "constants.h"
#include "convert.h"
#include "hex.h"

size_t round_up_block(size_t in_len){
	if(in_len % BLOCK_SIZE)
		return in_len + BLOCK_SIZE - (in_len % BLOCK_SIZE);
	return in_len;
}

char* convert_from(char* buffer, char* mode, size_t* len){
	char *newbuf = 0;
	size_t newlen = 0;
	int i;
	if(!strcmp(mode, "raw")){
		// pad the block
		newlen = round_up_block(*len);
		// realloc padded buffer
		newbuf = realloc(buffer, sizeof(char) * (newlen + 1));
		// fill pad with 0s
		for(i = *len; i < newlen; i++)
			newbuf[i] = 0;
	}
	else if(!strcmp(mode, "hex")){
		// 2 hex digits per byte, and pad
		newlen = round_up_block(*len / 2);
		// alloc new buffer
		newbuf = malloc(sizeof(char) * (newlen + 1));
		// perform conversion
		from_hex(buffer, newbuf, *len/2);
		// null terminate
		for(i = *len / 2; i < newlen; i++)
			newbuf[i] = 0;
		// free original buffer
		free(buffer);
	}
	else if(!strcmp(mode, "b64")){
		// TODO
		fprintf(stderr, "b64 mode is not implemented yet.\n");
		exit(1);
	}
	else{
		fprintf(stderr, "error: invalid conversion mode '%s'\n", mode);
	}
	*len = newlen;
	return newbuf;
}

char* convert_to(char* buffer, char* mode, size_t* len){
	char *newbuf;
	if(!strcmp(mode, "raw")){
		// do nothing
		*len = *len;
		newbuf = buffer;
	}
	else if(!strcmp(mode, "hex")){
		// 2 hex digits per byte
		*len = *len * 2;
		// alloc new buffer
		newbuf = malloc(sizeof(char) * (*len + 1));
		// perform conversion
		to_hex(buffer, newbuf, *len/2, 0);
		// free original buffer
		free(buffer);
	}
	else if(!strcmp(mode, "b64")){
		// TODO
		fprintf(stderr, "b64 mode is not implemented yet.\n");
		exit(1);
	}
	else{
		fprintf(stderr, "error: invalid conversion mode '%s'\n", mode);
	}
	return newbuf;
}
