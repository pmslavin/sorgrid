TARGET  := sorgrid
CC      := gcc
CFLAGS  := -std=c99 -O3
WARN    := -Wall -Wextra -Wno-format -pedantic
# Libs required can be system-dependent; min is -lglut, max as below.
LIBS    := -lm -lglut -lGL -lGLU
OBJECTS := sor.o grid.o

all:	sorgrid

sorgrid: ${OBJECTS}
	${CC} ${OBJECTS} -o sorgrid ${LIBS}

sor.o: sor.c sor.h
	${CC} ${WARN} -c sor.c

grid.o: grid.c grid.h sor.h
	${CC} ${WARN} -c grid.c

clean:
	-rm *.o sorgrid
