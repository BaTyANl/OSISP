CC = gcc
.PHONY: clean
all: program
program: main.c stack.c ring.c makefile
	$(CC) main.c stack.c ring.c -pthread -o program
clean:
	rm program