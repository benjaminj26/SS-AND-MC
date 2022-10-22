FILE = src/Round_Robin.c
PROG = build/Round_Robin

CC = gcc
CFLAGS = -Wall -o

${PROG}: ${FILE}
	${CC} ${CFLAGS} ${PROG} ${FILE}

run: ${PROG}
	./${PROG}

clean: ${PROG}
	rm ${PROG}