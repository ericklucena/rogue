CC=gcc
CPPFLAGS=
CFLAGS= -std=c99 -Wall -pedantic -Iinclude -g
LDFLAGS= -lncurses -lm

all: src/*.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o bin/runMe

test: src/util.c src/parser.c src/rogue.c src/io.c src/graphics.c tests/test.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o bin/test

clean: 
	rm bin/runMe
	rm bin/test
