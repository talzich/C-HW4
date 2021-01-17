CFLAGS = -Wall
CC = gcc

all: frequency

frequency: frequency.c
	$(CC) $(CFLAGS) frequency.c -o frequency

.PHONY: clean

clean:
	rm -rf frequency