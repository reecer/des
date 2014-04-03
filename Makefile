# Flags and such

CC=gcc
CCFLAGS=-Wall

LIB_SOURCES=$(wildcard src/*.c)
LIB_OBJECTS=$(addprefix obj/,$(notdir $(LIB_SOURCES:.c=.o)))
LIB_TARGET=lib/libdes.a

TST_SOURCES=$(wildcard tests/*.c)
TST_TARGETS=$(TST_SOURCES:.c=)

# General stuff

all: libdes tests

clean:
	rm -rf $(LIB_OBJECTS) $(LIB_TARGET) $(TST_TARGETS) lib inc obj

# Library stuff

libdes: $(LIB_OBJECTS)
	@echo "* * * Creating libdes archive..."
	mkdir -p lib
	ar -cvq $(LIB_TARGET) $(LIB_OBJECTS)
	@echo "* * * Copying include headers..."
	mkdir -p inc/des
	cp src/convert.h inc/des/convert.h
	cp src/keygen.h inc/des/keygen.h
	cp src/read.h inc/des/read.h
	cp src/hex.h inc/des/hex.h
	cp src/des_wrapper.h inc/des/des.h

obj/%.o: src/%.c src/%.h obj/
	$(CC) $(CCFLAGS) -c -o $@ $<

obj/%.o: src/%.c obj/
	$(CC) $(CCFLAGS) -c -o $@ $<

obj/: 
	@echo "* * * Compiling libdes objects..."
	mkdir -p obj
	
# Test stuff
	
tests: tests_p $(TST_TARGETS)
	
tests_p:
	@echo "* * * Compiling test programs..."

tests/%: tests/%.c
	$(CC) $(CCFLAGS) -L./lib/ -I./inc/ -o $@ $< -ldes
	

