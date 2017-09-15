CC=clang
CFLAGS = -std=c99 -Wall -pedantic -g -Llib64 -lruntime
SOURCE=$(wildcard *.c)

all: pa4

pa4: $(SOURCE)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm *.log pa4

.PHONY: tar
tar:
	tar -zcf ../pa4.tar.gz ../pa4
