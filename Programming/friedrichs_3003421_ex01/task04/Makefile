binary=editstack

all: $(binary).o
	gcc -std=c11 -fno-stack-protector $(binary).o -o $(binary)

$(binary).o: $(binary).c
	gcc -std=c11 -fno-stack-protector -c editstack.c

debug: $(binary).c
	gcc  -S -g $(binary).c
	
clean:
	rm *.o *.s $(binary)
