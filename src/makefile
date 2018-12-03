CC = gcc
CFLAGS = -g

EXE = test

all: $(EXE)


test: test.o core.o
	$(CC) $(CFLAGS) -o test test.o core.o

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

core.o: core.c core.h
	$(CC) $(CFLAGS) -c core.c

.PHONY:
clean:
	rm -f $(EXE) *.o
