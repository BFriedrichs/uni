binary=imagecopy
all: main.o
	gcc -std=c11 -ljpeg main.o -o $(binary)

main.o: main.c
	gcc -std=c11 -c main.c

clean:
	rm *.o $(binary)
