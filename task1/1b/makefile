all: 1b
 
1b: 1b.o 
	gcc -Wall  -g  -o 1b 1b.o 
1b.o : 1b.c
	gcc -Wall  -g -c 1b.c
clean:
	rm -f *.o  1b
