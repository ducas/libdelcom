
SONAME=libdelcom.so
ONAME=delcom.o
CC=gcc
CFLAGS=-c -Wall -Werror -fpic
LFLAGS=-lhid
SFLAGS=-shared -o

all: delcom.so

delcom.so: delcom.o
	$(CC) $(SFLAGS) $(SONAME) $(ONAME) $(LFLAGS)

delcom.o:
	$(CC) $(CFLAGS) delcom.c $(LFLAGS)

install: all
	cp libdelcom.so /usr/local/lib/
	cp delcom.h /usr/include/
	ldconfig

uninstall:
	rm /usr/local/lib/libdelcom.so
	rm /usr/include/delcom.h
	ldconfig
	
clean:
	rm -rf libdelcom.* delcom.o
