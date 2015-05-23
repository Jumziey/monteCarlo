CC = gcc
CPPFLAGS = -DCLU -DVIS
CFLAGS  = -g -O4
LOADLIBES = -lm -lg2
VPATH = ../src

INCLUDES = ran.h ising.h visualize.h

OBJS = ising.o ran.o config.o cluster.o visualize.o

ising: ${OBJS}

summary: summary.o

${OBJS}: ${INCLUDES} Makefile

clean:
	rm *.o ising
