test-bigint.c: bigints.o test-bigint.c
	gcc -ansi bigints.o test-bigint.c \
		-o test.exe

voting.exe: bigints.o encryption.o voting.c
	gcc -Wall -ansi -pedantic bigints.o encryption.o file-man.o voting.c \
		-o voting.exe

file-man.o: file-man.c file-man.h
	gcc -c -Wall -ansi -pedantic file-man.c

encryption.o: bigints.o encryption.c encryption.h
	gcc -c -Wall -ansi -pedantic encryption.c

bigints.o: bigints.c bigints.h
	gcc -c -Wall -ansi -pedantic bigints.c
