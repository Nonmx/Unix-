SOURCE = 5-3_modify.c
OBJ = 5-3.o
OUT = run
CC = gcc
CFLAGS = -o

${OUT}:${OBJ}
	${CC} ${OBJ} ${CFLAGS} ${OUT}

${OBJ}:${SOURCE}
	${CC} -D_FILE_OFFSET_BITS=64 ${SOURCE} -c ${CFLAGS} ${OBJ}

clean:
	rm -f *.o run

