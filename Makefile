CC=gcc
CPPFLAGS=
CFLAGS= -std=c99 -Wall -pedantic -Iinclude -lm -g
LDFLAGS= -lncurses

all: src/*.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o bin/runMe

test: src/file.c src/memory.c src/logo.c src/util.c src/parser.c tests/test.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o bin/test

clean: 
	rm bin/runMe
	rm bin/test
