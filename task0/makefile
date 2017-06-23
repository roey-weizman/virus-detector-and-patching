all: main
 
main: main.o 
	gcc -Wall  -g  -o main main.o 
main.o : main.c
	gcc -Wall  -g -c main.c
clean:
	rm -f *.o  main
