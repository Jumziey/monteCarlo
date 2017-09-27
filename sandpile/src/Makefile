CC = gcc
#CPPFLAGS = -DVIS
CFLAGS  = -g -O2
LOADLIBES = -lm -lg2

INCLUDES = ran.h visualize.h
OBJS = sandpile.o ran.o visualize.o

sandpile: ${OBJS}

${OBJS}: ${INCLUDES}

clean:
	rm *.o sandpile
