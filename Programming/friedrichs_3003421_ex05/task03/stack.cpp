#include "stack.hpp"

/**
 * Stack default constructor
 * Prints Ctor mesage and allocates memory on heap.
 *
 * @param int size - default: 10 - Sets the stack size
 */
Stack::Stack(int size) {
    this->size = size;
    this->currentPointer = this->stackPointer = (int*) calloc(this->size, sizeof(int));
}

/**
 * Stack copy constructor
 * Prints Cctor mesage and copys obj to new object.
 *
 * @param const Stack &obj - Object to be copied
 */
Stack::Stack(const Stack &obj) : size(obj.size) {
    this->currentPointer = this->stackPointer = (int*) calloc(this->size, sizeof(int));
    memcpy(this->stackPointer, obj.stackPointer, sizeof(int) * this->size);
    this->currentPointer += obj.length();
}

/**
 * Stack move constructor
 * Prints Mctor mesage and moves obj to new object.
 *
 * @param Stack &&obj - Object to be moved
 */
Stack::Stack(Stack &&obj) : size(obj.size), currentPointer(obj.currentPointer) {
    free(this->stackPointer);   // free old stack

    this->stackPointer = obj.stackPointer;  //after freeing we can move the sp too

    // unset moved object
    obj.size = 0;
    obj.currentPointer = obj.stackPointer = NULL;
}

/**
 * Stack destructor
 * Prints Dtor mesage and frees memory
 */
Stack::~Stack() {
    free(this->stackPointer);
}

/**
 * Stack copy operator
 * Prints Cop= mesage and copys obj into new object and returns pointer to it.
 *
 * @param const Stack &obj - Object to be copied
 * @return Stack* - Pointer to the created object
 */
Stack &Stack::operator=(const Stack &obj) {
    free(this->stackPointer);   // old stack not needed any longer

    this->size = obj.size;
    this->currentPointer = this->stackPointer = (int*) calloc(this->size, sizeof(int));
    memcpy(this->stackPointer, obj.stackPointer, sizeof(int) * this->size);
    this->currentPointer += obj.length();

    return *this;
}

/**
 * Stack move operator
 * Prints Mop= mesage and move obj into new object and returns pointer to it.
 *
 * @param Stack &&obj - Object to be moved
 * @return Stack* - Pointer to the created object
 */
Stack &Stack::operator=(Stack &&obj) {
    free(this->stackPointer);   // free old stack

    // move copy everything to new object first
    this->size = obj.size;
    this->stackPointer = obj.stackPointer;
    this->currentPointer = obj.currentPointer;

    // unset old, moved object
    obj.size = 0;
    obj.currentPointer = obj.stackPointer = NULL;

    return *this;
}

/**
 * Is stack full?
 *
 * @return bool - is the stack full?
 */
bool Stack::is_full() {
    return this->currentPointer == this->stackPointer + this->size;
}

/**
 * Is stack empty?
 *
 * @return bool - is the stack empty?
 */
bool Stack::is_empty() {
    return this->currentPointer == this->stackPointer;
}

/**
 * Adds a number to the stack and increases the stack pointer
 * if it isn't full.
 *
 * @param int num - number to add
 */
void Stack::push(int num) {
    if(this->is_full()) {
        std::cout << "The stack is full" << std::endl;
    } else {
        *(this->currentPointer++) = num;
    }
}

/**
 * Returns the last number on the stack and decreases stack pointer
 * if it isn't empty. Else it returns 0.
 *
 * @return int - Last number on stack or 0 if empty
 */
int Stack::pop() {
    if(this->is_empty()) {
        std::cout << "The stack is empty" << std::endl;
    } else {
        return *(--this->currentPointer);
    }
    return 0;
}

/**
 * Prints every number on the stack with a space as delimiter.
 */
void Stack::show() const {
    int *temp = this->stackPointer;

    while(temp != this->currentPointer) {
        std::cout << *temp << " ";
        temp++;
    }
    std::cout << std::endl;
}

/**
 * Returns the stack capacity.
 *
 * @return int - stack capacity
 */
int Stack::capacity() const {
    return this->size;
}

/**
 * Returns the number of numbers on the stack.
 *
 * @return int - Amount of items on the stack
 */
int Stack::length() const {
    return this->currentPointer - this->stackPointer;
}