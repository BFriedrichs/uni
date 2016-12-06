binary=stopwatch
file=ex04task04

all: $(file).o
	g++ -std=c++11 $(file).cpp -o $(binary)

$(file).o: $(file).cpp
	g++ -std=c++11 -c $(file).cpp

clean:
	rm *.o $(binary)
