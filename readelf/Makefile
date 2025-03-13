CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic
TARGET = 0-hreadelf

all: $(TARGET)

$(TARGET): 0-hreadelf.o
	$(CC) $(CFLAGS) -o $(TARGET) 0-hreadelf.o

0-hreadelf.o: 0-hreadelf.c
	$(CC) $(CFLAGS) -c 0-hreadelf.c

clean:
	rm -f *.o $(TARGET)