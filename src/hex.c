#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hex.h"

const char HEX_MAP[] = "0123456789abcdef";

void to_hex(char* input, char* output, int len, int with_space){
	char *i, *j;
	for(i = input, j = output; i < input + len; i++){
		*j++ = HEX_MAP[*i >> 4 & 0xF];
		*j++ = HEX_MAP[*i & 0xF];
		if(with_space)
			*j++ = ' ';
	}
	*j = '\0';
}

void from_hex(char *input, char *output, int len){
	int i, z;
	for(i = 0, z = 0; i < len; i++){
		int j = 0;
		char byte = 0;
    	while(j<2 && *(input+z)){
			char c = *(input+z);
        	int n = 0;
        	if( '0'<=c && c<='9' ){
            	n = c-'0';
            	z++;
            }
        	else if( 'a'<=c && c<='f' ){
            	n = 10 + c-'a';
            	z++;
            }
        	else if( 'A'<=c && c<='F' ){
            	n = 10 + c-'A';
            	z++;
            }
            else {
            	z++;
            	continue;
            }
        	byte = n + byte*16;
        	j++;
    	}
    	output[i] = byte;
	}

}

void print_hex(char* input, int len, int with_space){
	char* output = malloc(len * (with_space?3:2) + 1);
	to_hex(input, output, len, with_space);
	printf("%s\n",output);
	free(output);
}

void print_hex_wrap(char* input, int len, int size, int with_space){
	int width = (with_space?3:2), mod = (with_space?(size-2)/3+1:size/2), i;
	char *output = malloc(width*len+1), div = (with_space?' ':'\0');
	to_hex(input, output, len, with_space);
	for(i = 0; i < len; i++)
		printf("%c%c%c", output[width*i], output[width*i+1], (i==len-1||i%mod==mod-1)?'\n':div);
	free(output);
}
