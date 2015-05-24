CC = gcc
CFLAGS  = -g -O4 --std=c99
LOADLIBES = -lm -lg2
VPATH = ../src

INCLUDES = ran.h ising.h visualize.h

OBJS = ising.o config.o ran.o metro.o visualize.o

ising: ${OBJS}

summary.o: ising.h

summary: summary.o

gtot: gtot.o

${OBJS}: ${INCLUDES} Makefile

clean:
	rm ising *.o
