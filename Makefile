CC=gcc
LIBS=-lkeyutils
CFLAGS=

all: key_copy

clean:
	rm -f *.o key_copy

key_copy: key_copy.o
	${CC} -o key_copy key_copy.o ${LIBS}

key_copy.o: key_copy.c
	${CC} -c -o key_copy.o key_copy.c ${CFLAGS}
