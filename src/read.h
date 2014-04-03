#ifndef read_h
#define read_h

/**
  read_stdin:
    Reads stdin until EOF and stores it in a malloc'd buffer. Returns that buffer and stores its length in len.
    Length does not include null terminator (similar to strlen function).
*/
char* read_stdin(size_t* len);

/**
  read_blocks:
    Similar to read_stdin, but for any opened file handle.
*/
char* read_blocks(size_t* len, FILE* f);

#endif
