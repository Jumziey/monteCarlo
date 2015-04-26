CC = gcc
CPPFLAGS = -DCLU
CFLAGS  = -g -O4
LOADLIBES = -lm
VPATH = ../src

INCLUDES = ran.h ising.h

OBJS = ising.o ran.o config.o cluster.o

ising: ${OBJS}

summary: summary.o

${OBJS}: ${INCLUDES} Makefile
