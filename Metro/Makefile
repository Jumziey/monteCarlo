CC = gcc
CFLAGS  = -g -O4 --std=c99
LOADLIBES = -lm
VPATH = ../src

INCLUDES = ran.h update.h

OBJS = ising.o config.o ran.o metro.o

ising: ${OBJS}

summary.o: ising.h

summary: summary.o

gtot: gtot.o

${OBJS}: ${INCLUDES} Makefile

clean:
	rm ising *.o
