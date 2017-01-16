binary=chat

all:
	/usr/bin/g++ -std=c++11 -stdlib=libc++ -pthread -I'headers/' src/*.cpp main.cpp -o $(binary)

clean:
	rm *.o $(binary)
