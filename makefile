all:	programB programA
programA: programA.o arg.o file_lib.o complex_number.o 
	gcc -o programA  programA.o arg.o file_lib.o complex_number.o

programB: programB.o arg.o file_lib.o complex_number.o 
	gcc -o programB  programB.o arg.o file_lib.o complex_number.o

arg.o : arg.c
	gcc -c	arg.c

file_lib.o : file_lib.c
	gcc -c	file_lib.c

complex_number.o : complex_number.c
	gcc -c	complex_number.c

programA.o :programA.c
	gcc -c	programA.c

programB.o :programB.c
	gcc -c	programB.c

clear:
	rm *.o 
