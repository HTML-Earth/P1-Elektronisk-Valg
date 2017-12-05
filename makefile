test.exe: bigints.o test-bigint.c
	gcc -ansi bigints.o test-bigint.c \
		-o test.exe

main.exe: bigints.o encryption.o voting.o file-man.o main.exe
	gcc -Wall -ansi -pedantic bigints.o encryption.o file-man.o voting.o main.c \
		-o main.exe

file-man.o: file-man.c file-man.h
	gcc -c -Wall -ansi -pedantic file-man.c

encryption.o: bigints.o encryption.c encryption.h
	gcc -c -Wall -ansi -pedantic encryption.c

bigints.o: bigints.c bigints.h
	gcc -c -Wall -ansi -pedantic bigints.c

voting.o: voting.c voting.h
	gcc -c -Wall -ansi -pedantic voting.c
