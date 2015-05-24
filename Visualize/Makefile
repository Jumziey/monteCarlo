CC = gcc
CPPFLAGS = -DVIS
CFLAGS  = -g -O2
LOADLIBES = -lm -lg2
VPATH = ../src

INCLUDES = ran.h ising.h visualize.h

OBJS = ising.o ran.o config.o visualize.o

metro: ${OBJS} metro.o

cluster: ${OBJS} cluster.o

summary: summary.o

${OBJS}: ${INCLUDES} Makefile

clean:
	rm *.o cluster metro
