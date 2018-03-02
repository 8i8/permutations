EXE = permutations
SRC = permutations.c trie.c
OBJ = $(SRC:.c=.o)
CC = gcc
#CFLAGS = -g
CFLAGS += -Wall -Wextra -pedantic
#CFLAGS += -fsanitize=address -fno-omit-frame-pointer

.PHONY: all clean

all:	$(EXE)

clean:
	rm -f *.o $(EXE)
	
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)

$(OBJ): trie.h Makefile
