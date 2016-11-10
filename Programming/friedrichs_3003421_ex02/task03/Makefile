binary=calc

all: main.o
	gcc -std=c11 main.o -o $(binary) -lm 

main.o: main.c
	gcc -std=c11 -c main.c

clean:
	rm *.o $(binary)
