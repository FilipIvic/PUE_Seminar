#FLAGS = -Wall
FLAGS = -Wall -O3
TARGETS = pokreni
CC = /usr/bin/gcc

default: pokreni

all: $(TARGETS)

pokreni: pokreni.o
	$(CC) $(FLAGS) pokreni.o -o pokreni


.c.o: 
	$(CC) $(FLAGS) -c $<

clean:
	rm -f *.o *~ $(TARGETS)
	