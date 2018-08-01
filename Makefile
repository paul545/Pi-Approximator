#
#Paul Bosonetto
#

CC = gcc
CFLAGS = -O -Wall -pthread
LFLAGS = 

all: my-pi

my-pi: main.c children.c children.h
	$(CC) $(CFLAGS) -c -o children.o children.c
	$(CC) $(CFLAGS) -c -o main.o main.c
	$(CC) $(CFLAGS) -o my-pi main.o children.o
	
clean:
	rm -f children.o main.o my-pi.c
