GCC  = gcc
OBJ = ./
BIN = ./

SRC = $(wildcard *.c)
TAR = $(SRC:.c=)
CFLAGS = -Wall

.PHONY: all clean

all: $(TAR)

%: %.c
	$(GCC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(OBJ)*.o $(TAR)