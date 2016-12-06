#include <iostream>
#include "stopwatch.hpp"
#include "stack.hpp"

#define MEASURETIME(description, repetitions, instructions2test) {              \
                _W.start();                                                     \
                for(int _ITER = 0; _ITER < repetitions; _ITER++) {              \
                    instructions2test;                                          \
                }                                                               \
                std::cout << "My computer requires ";                           \
                std::cout << _W.stop() << " ";                                  \
                std::cout << "seconds to execute ";                             \
                std::cout << description << " ";                                \
                std::cout << repetitions << " ";                                \
                std::cout << "times" << std::endl; }

StopWatch _W;

int main() {
    Stack s1(100000);
    Stack s2;
    Stack s3;

    for(int i = 0; i < 100000; i++) {
        s1.push(i*3);
    }

    MEASURETIME("Copy assignment test", 10000, s2 = s1)
    MEASURETIME("Move assignment test", 10000, s3 = s1.length())
}

