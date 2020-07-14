SOURCE = 5-3.c
OBJ = 5-3.o
OUT = run
CC = gcc
CFLAGS = -o

${OUT}:${OBJ}
	${CC} ${OBJ} ${CFLAGS} ${OUT}

${OBJ}:${SOURCE}
	${CC} ${SOURCE} -c ${CFLAGS} ${OBJ}

clean:
	rm -f *.o run

