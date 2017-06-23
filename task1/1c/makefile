all: 1c
 
1c: 1c.o 
	gcc -Wall  -g  -o 1c 1c.o 
1c.o : 1c.c
	gcc -Wall  -g -c 1c.c
clean:
	rm -f *.o  1c
