CC = gcc
CFLAGS = -O2

INC = ../../src
SRCS = $(INC)/gui.o

all: conn4

conn4: conn4.o $(SRCS)
	$(CC) $(CFLAGS) -o conn4 conn4.o $(SRCS)

conn4.o: conn4.c conn4.h
	$(CC) $(CFLAGS) -c conn4.c -I$(INC)

.PHONY:
clean:
	rm -f *.o conn4
