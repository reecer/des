#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "read.h"

#define BUF_SIZE 1024

char* read_stdin(size_t* len){
	return read_blocks(len, stdin);
}

char* read_blocks(size_t* len, FILE* f){
	char buffer[BUF_SIZE];
	size_t s = 0, bs;

	char *content = malloc(sizeof(char) * (BUF_SIZE+1));
	
	if(content == NULL){
		fprintf(stderr,"memory allocation error in read_blocks\n");
		exit(EXIT_FAILURE);
	}
	
	memset(content, 0, BUF_SIZE+1);

	while((bs = fread(buffer, sizeof(char), BUF_SIZE, f)) != 0 ){
		char *old = content;
    	content = realloc(content, s+bs+1);
		if(content == NULL){
        	fprintf(stderr,"memory allocation error in read_blocks\n");
			free(old);
			exit(EXIT_FAILURE);
		}
		memcpy(content + s, buffer, bs);
		s += bs;
		memset(buffer, 0, BUF_SIZE);
	}

	if(ferror(f)){
		free(content);
		fprintf(stderr,"read error in read_blocks\n");
		exit(EXIT_FAILURE);
	}
	
	*len = s;
	
	return content;
}
