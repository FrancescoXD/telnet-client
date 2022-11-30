CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic
FILES = ./src/telnet.c
OUTPUT = ./build/telnet

.PHONY: clean

clean:
	rm -rf build/

build:
	mkdir build/
	$(CC) $(FILES) -o $(OUTPUT) $(CFLAGS)

