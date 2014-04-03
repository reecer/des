#ifndef hex_h
#define hex_h

/**
HEX_MAP:
  An array associating a 4-bit value to a hexadecimal character.
*/
extern const char HEX_MAP[];

/**
to_hex:
  Converts char array 'input' to hexadecimal and writes the resulting string
  to the buffer 'output', which for input size n (excluding null terminator)
  must be of size 2n+1 (including null terminator) if 'with_space' is zero,
  or 3n+1 if 'with_space' is nonzero.
*/
void to_hex(char* input, char* output, int len, int with_space);

/**
from_hex:
  Converts string of hexadecimal digits to a binary character array
*/
void from_hex(char* input, char* output, int len);

/**
print_hex:
  Prints out the hexadecimal represntation of array 'input', with or without
  spaces as specified by 'with_space'.
*/
void print_hex(char* input, int len, int with_space);

/**
print_hex_wrap:
  Prints the hexadecimal representation of 'input' with lines wrapped to a
  maximum of 'size' characters, with or without spaces as specified by 
  'with_space'.
*/
void print_hex_wrap(char* input, int len, int size, int with_space);

#endif
