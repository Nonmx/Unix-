SOURCE = 5.3.c
OBJ = 5.3.o
OUT = atomic_append
CC = gcc
CFLAGS = -o

${OUT}:${OBJ}
	${CC} ${OBJ} ${CFLAGS} ${OUT}

%.o:%.c
	${CC} ${SOURCE} -c ${CFLAGS} $@

clean:
	rm -f *.o atomic_append
