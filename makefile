voting.exe: bigints.o encryption.o decryption.o voting.c
	gcc -Wall -ansi -pedantic bigints.o encryption.o decryption.o voting.c \
		-o voting.exe

encryption.o: bigints.o encryption.c encryption.h
	gcc -c -Wall -ansi -pedantic bigints.o encryption.c

decryption.o: decryption.c decryption.h
	gcc -c -Wall -ansi -pedantic bigints.o decryption.c

bigints.o: bigints.c bigints.h
	gcc -c -Wall -ansi -pedantic bigints.c
