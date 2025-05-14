CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -g
OBJS = strace_0.o

.PHONY: all clean

all: strace_0 strace_1

strace_0: $(OBJS)
	$(CC) $(CFLAGS) -o strace_0 $(OBJS) $(LDFLAGS)

strace_0.o: strace_0.c strace_1.c syscalls.h
	$(CC) $(CFLAGS) -c strace_0.c strace_1.c

clean:
	rm -f strace_0 $(OBJS) *~ core* *.core *.dSYM
