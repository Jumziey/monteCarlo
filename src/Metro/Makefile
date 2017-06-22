CC = gcc
CFLAGS  = -g -O4 --std=c99
LOADLIBES = -lm -lg2
VPATH = ../../src

INCLUDES = ising.h ran.h visualize.h timecorr.h save.h

OBJS = ising.o config.o ran.o metro.o timecorr.o save.o

metro: ${OBJS}

summary.o: ising.h

summary: summary.o

gtot: gtot.o

${OBJS}: ${INCLUDES} Makefile

clean:
	rm metro *.o
