#ifndef convert_h
#define convert_h

/**
convert_from:
  Takes input encoded using the specified 'mode' and converts it to raw.
  Realloc's the buffer to the length of the processed data, returns the new buffer, and saves the length in len.
*/
char* convert_from(char* buffer, char* mode, size_t* len);

/**
convert_to:
  Takes raw input and encodes it using the specified 'mode'.
  Realloc's the buffer to the length of the processed data, returns the new buffer, and saves the length in len.
*/
char* convert_to(char* buffer, char* mode, size_t* len);

#endif
