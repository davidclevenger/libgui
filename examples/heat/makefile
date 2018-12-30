CC = gcc
CFLAGS = -g

INC = ../../src
SRCS = $(INC)/gui.o

all: heat

heat: heat.o $(SRCS)
	$(CC) $(CFLAGS) -o heat heat.o $(SRCS)

heat.o: heat.c
	$(CC) $(CFLAGS) -c heat.c -I$(INC)

.PHONY:
clean:
	rm -f *.o heat
