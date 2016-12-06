#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#ifndef STACK_H
#define STACK_H

/**
 * \class Stack
 *
 * Stores int values as a stack.
 */
class Stack {
    private:
        int *stackPointer;
        int *currentPointer;
        int size;

    public:
        Stack(int size=10);
        Stack(const Stack &obj);
        Stack(Stack &&obj);
        ~Stack();
        Stack &operator=(const Stack &obj);
        Stack &operator=(Stack &&obj);

        bool is_full();
        bool is_empty();
        void push(int num);
        int pop();
        void show() const;
        int capacity() const;
        int length() const;
};

#endif