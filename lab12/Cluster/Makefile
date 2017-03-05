CC = gcc
CPPFLAGS = -DCLU
CFLAGS  = -g -O4
LOADLIBES = -lm -lg2
VPATH = ../src

INCLUDES = ran.h ising.h timecorr.h

OBJS = ising.o ran.o config.o cluster.o timecorr.o

ising: ${OBJS}

summary: summary.o

${OBJS}: ${INCLUDES} Makefile

clean:
	rm *.o ising
