CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-lelf
RULE=hnm

SRCS=hnm.c
OBJS=$(SRCS:.c=.o)

all: $(RULE

$(RULE): $(OBJS)
    $(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS) $(RULE)