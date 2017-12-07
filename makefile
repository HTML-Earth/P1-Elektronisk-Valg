test.exe: bigints.o test-bigint.c
	gcc -ansi bigints.o test-bigint.c \
		-o test.exe

admin.exe: bigints.o encryption.o voting-functions.o file-man.o admin.exe
	gcc -Wall -ansi -pedantic bigints.o encryption.o file-man.o voting-functions.o admin.c \
		-o admin.exe
voting.exe: bigints.o encryption.o voting-functions.o file-man.o voting.exe
	gcc -Wall -ansi -pedantic bigints.o encryption.o file-man.o voting-functions.o voting.exe \
		-o voting.exe

file-man.o: file-man.c file-man.h
	gcc -c -Wall -ansi -pedantic file-man.c

encryption.o: bigints.o encryption.c encryption.h
	gcc -c -Wall -ansi -pedantic encryption.c

bigints.o: bigints.c bigints.h
	gcc -c -Wall -ansi -pedantic bigints.c

voting-functions.o: voting-functions.c voting-functions.h
	gcc -c -Wall -ansi -pedantic voting-functions.c
