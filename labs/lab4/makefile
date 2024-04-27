CC = gcc
.PHONY: clean
all: program
program: main.c stack.c ring.c makefile
	$(CC) main.c stack.c ring.c -o program
clean:
	rm program