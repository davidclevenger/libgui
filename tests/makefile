CC = gcc
CFLAGS =

SRC = ../src
SRCS = $(SRC)/gui.o
TESTS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(TESTS))
PROGS = $(patsubst %.c, %, $(TESTS))

all: $(PROGS)

$(PROGS): %: %.o $(SRCS)
	$(CC) $(CFLAGS) $< $(SRCS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I$(SRC)

.PHONY:
clean:
	rm -f $(OBJS) $(PROGS) *.o *.gch
