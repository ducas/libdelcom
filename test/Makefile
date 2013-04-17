
CC=gcc
CFLAGS=-c -Wall -Werror -fpic
LFLAGS=-lhid -ldelcom
OFLAGS=-Wall -o

all: test

test:
	$(CC) $(OFLAGS) test_delcom test_delcom.c $(LFLAGS)

clean:
	rm -rf test_delcom delcom.h
