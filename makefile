voting.exe: bigints.o encryption.o voting.c
	gcc -Wall -ansi -pedantic bigints.o encryption.o voting.c \
		-o voting.exe

encryption.o: bigints.o encryption.c encryption.h
	gcc -c -Wall -ansi -pedantic bigints.o encryption.c

bigints.o: bigints.c bigints.h
	gcc -c -Wall -ansi -pedantic bigints.c
