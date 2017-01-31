binary1=allcalls
binary2=overhead
binary3=casting

all:
	g++ -std=c++11 -DVERBOSE overhead.cpp classes.cpp stopwatch.cpp -o $(binary1)

task02:
	g++ -std=c++11 -DTASK02 overhead.cpp classes.cpp stopwatch.cpp -o $(binary2)

task03:
	g++ -std=c++11 -DTASK03 overhead.cpp classes.cpp stopwatch.cpp -o $(binary3)

clean:
	rm *.o $(binary1) $(binary2) $(binary3)
