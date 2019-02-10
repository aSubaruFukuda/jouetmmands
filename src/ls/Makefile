PROGRAM = `git rev-parse --show-toplevel`/bin/ls
OBJS	= ls.o
SRCS	= $(OBJS:%.o=%.c)
CC		= gcc
CFLAGS	= -g -Wall
LDFLAGS	=

$(PROGRAM):$(OBJS)
	$(CC) $(CFLAS) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LDLIBS)
	rm $(OBJS)
