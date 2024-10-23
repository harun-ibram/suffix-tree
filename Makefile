CC=gcc
CFLAGS=-Wall -Werror -g

run: build
	./main
build: main.o Tree.o Queue.o
	$(CC) $(CFLAGS) main.o Tree.o Queue.o -o main

main.o: main.c

Tree.o: Tree.c

Queue.o: Queue.c

clean:
	rm -rf main.o Queue.o Tree.o