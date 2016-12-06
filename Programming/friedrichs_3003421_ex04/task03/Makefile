binary=overflow
file=ex04task03

all: $(file).o
	gcc -std=c11 $(file).o -o $(binary)

$(file).o: $(file).c
	gcc -std=c11 -c $(file).c

clean:
	rm *.o $(binary)
