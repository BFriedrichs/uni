binary=scope

all: scope1.o scope2.o
	gcc -std=c11 -Wl,-E scope1.o scope2.o -o $(binary)

scope1.o: scope1.c
	gcc -std=c11 -c scope1.c

scope2.o: scope2.c
	gcc -std=c11 -c scope2.c

clean:
	rm *.o $(binary)
