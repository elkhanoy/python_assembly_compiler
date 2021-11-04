CFLAGS = -Wall -Wextra -g -Iinclude
LFLAGS =

TESTS_SRC = $(wildcard tests/*.c)
TESTS_BIN = $(TESTS_SRC:.c=.exe)

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all : $(OBJ) $(TESTS_BIN)

%.exe: %.o
	$(CC) $(OBJ) $< $(LFLAGS) -o $@

clean :
	$(RM) $(OBJ)
	$(RM) $(TESTS_BIN)
	find . -name "*~" -delete
