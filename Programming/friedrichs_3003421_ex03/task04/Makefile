binary=proportional

all: ../task01/main.c
	gcc -D DO_RESIZE -D KEEP_ASPECT ../task01/main.c -ljpeg -o $(binary)

clean:
	rm $(binary)
