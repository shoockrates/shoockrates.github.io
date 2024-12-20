CC = gcc
CFLAGS = -Wall -O2
LIBS = -lmicrohttpd

all: server

server: server.c
	$(CC) $(CFLAGS) -o server server.c $(LIBS)

clean:
	rm -f server

