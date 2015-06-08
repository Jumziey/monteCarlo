CC = gcc
#CPPFLAGS =
CFLAGS  = -g -O2
LOADLIBES = -lm

INCLUDES = ran.h
OBJS = sandpile.o ran.o

sandpile: ${OBJS}

${OBJS}: ${INCLUDES}

clean:
	rm *.o sandpile
