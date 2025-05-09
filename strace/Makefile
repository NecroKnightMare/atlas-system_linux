CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =
OBJS = strace_0.o

.PHONY: all clean

all: strace_0

strace_0: $(OBJS)
	$(CC) $(CFLAGS) -o strace_0 $(OBJS) $(LDFLAGS)

strace_0.o: strace_0.cpp syscalls.h
	$(CC) $(CFLAGS) -c strace_0.cpp

clean:
	rm -f strace_0 $(OBJS) *~ core* *.core *.dSYM
