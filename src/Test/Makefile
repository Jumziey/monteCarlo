CC = gcc
CPPFLAGS = -DCLU
CFLAGS  = -g -O4
LOADLIBES = -lm -lg2
VPATH = ../

INCLUDES = save.h 

OBJS = save.o 

test: ${OBJS}

${OBJS}: ${INCLUDES} Makefile

clean:
	rm *.o test
