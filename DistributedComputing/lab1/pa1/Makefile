CC=clang
CFLAGS = -std=c99 -Wall -pedantic -g
SOURCE=$(wildcard *.c)

all: pa1

pa1: $(SOURCE)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm *.log pa1
