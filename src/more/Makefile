PROGRAM = `git rev-parse --show-toplevel`/bin/more
OBJS = more.o
SRCS = $(OBJS:%.o=.c)
CC = gcc
CFLAGS = -g -Wall
LDFLAGS =
$(PROGRAM):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LDLIBS)
	rm $(OBJS)

