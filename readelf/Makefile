.PHONY: all clean rebuild debug

SRC = 0-hreadelf.c
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic
EXEC = 0-hreadelf

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJ)

rebuild: clean all

debug: CFLAGS += -g
debug: rebuild