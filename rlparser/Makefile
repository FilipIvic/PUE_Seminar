FLAGS = -Wall -O3
TARGETS = rlparser
LIBS = -lreadline

CC = /usr/bin/gcc

default: rlparser

all: $(TARGETS)

rlparser: rlparser.o
	$(CC) $(FLAGS) rlparser.o $(LIBS) -o rlparser


.c.o: 
	$(CC) $(FLAGS) -c $<

clean:
	rm -f *.o *~ $(TARGETS)
	