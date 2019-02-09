PROGRAM = `git rev-parse --show-toplevel`/bin/logout
OBJS	= main.o logout.o
SRCS	= $(OBJS:%.o=%.c)
CC		= gcc
CFLAGS	= -g -Wall
LDFLAGS	=

$(PROGRAM):$(OBJS)
	$(CC) $(CFLAS) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LDLIBS)
	rm $(OBJS)
