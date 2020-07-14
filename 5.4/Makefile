SOURCE = 5.4.c
OBJ = 5.4.o
OUT = run
CC = gcc
CFLAGS = -o

${OUT}:${OBJ}
	${CC} ${OBJ} ${CFLAGS} ${OUT}

%.o:%.c
	${CC} ${SOURCE} -c ${CFLAGS} $@

clean:
	rm -f *.o run
