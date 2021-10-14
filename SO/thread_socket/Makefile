# Compiler settings
CC = gcc
CFLAGS = -Wall -Os -g
TFLAG = -lpthread

# Folders
BIN = bin

# Files
c_server = server_tcp.c
c_client = client_tcp.c
server = $(BIN)/server
client = $(BIN)/client


all: test1

$(server): $(c_server)
	$(CC) $(CFLAGS) -o $@ $^ $(TFLAG)

$(client): $(c_client)
	$(CC) $(CFLAGS) -o $@ $^ $(TFLAG)


test1: $(server)
	./$(server) 8888

test2: $(client)
	./$(client) 127.0.0.1 8888