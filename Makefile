all: admin.exe voting.exe test.exe clean

CC = gcc
CFLAGS = -Wall -ansi -pedantic


test.exe: bigints.o test-bigint.c
	${CC} -ansi bigints.o test-bigint.c \
		-o test.exe

admin.exe: bigints.o encryption.o voting-functions.o file-man.o
	${CC} ${CFLAGS} bigints.o encryption.o file-man.o voting-functions.o admin.c \
		-o admin.exe
voting.exe: bigints.o encryption.o voting-functions.o file-man.o
	${CC} ${CFLAGS} bigints.o encryption.o file-man.o voting-functions.o voting.c \
		-o voting.exe

file-man.o: file-man.c file-man.h
	${CC} ${CFLAGS} -c file-man.c

encryption.o: bigints.o encryption.c encryption.h
	${CC} ${CFLAGS} -c encryption.c

bigints.o: bigints.c bigints.h
	${CC} ${CFLAGS} -c bigints.c

voting-functions.o: voting-functions.c voting-functions.h
	${CC} ${CFLAGS} -c voting-functions.c

clean:
	rm -f *.o
