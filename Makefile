TARGET  := sorgrid
CC      := gcc
WARN    := -Wall 
# Libs required can be system-dependent; min is -lgluti, max as below.
LIBS    := -lm -lglut -lGL -lGLU
OBJECTS := sor.o grid.o

all:	sorgrid

sorgrid: ${OBJECTS}
	${CC} ${OBJECTS} -o sorgrid ${LIBS}

sor.o: sor.c sor.h
	${CC} ${WARN} -c sor.c

grid.o: grid.c grid.h sor.h
	${CC} ${WARN} -c grid.c
