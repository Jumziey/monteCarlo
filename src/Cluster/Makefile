CC = gcc
CPPFLAGS = -DCLU
CFLAGS  = -g -O4
LOADLIBES = -lm -lg2
VPATH = ../../src

INCLUDES = ran.h ising.h timecorr.h save.h

OBJS = ising.o ran.o config.o cluster.o timecorr.o save.o

cluster: ${OBJS}

summary: summary.o

${OBJS}: ${INCLUDES} Makefile

clean:
	rm *.o cluster
