binary=macromax
file=ex04task01

all: $(file).o
	g++ -std=c++11 $(file).o -o $(binary)

$(file).o: $(file).cpp
	g++ -std=c++11 -c $(file).cpp

clean:
	rm *.o $(binary)
