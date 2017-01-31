#ifndef RBUFFER_H
#define RBUFFER_H

#include <iostream>
#include <stdexcept>
/**
 * @class RingBuffer
 * @brief Template takes a class and a size
 */
template<class T, int RB_SIZE>
class RingBuffer {
  public:
    /**
     * @brief Default constructor, initialize the buffer
     */
    RingBuffer() : size(RB_SIZE), front(0), back(0), count(0) {
      this->buffer = new T[this->size];
    }

    /**
     * @brief Pushes an element to the front of the ringbuffer, drops the element silently if its full
     *
     * @param T - the element that is supposed to be pushed
     */
    void push_front(const T &in) {
      if(!this->full()) {
        this->buffer[this->front] = in;
        this->front = (this->front + 1) % this->size;
        this->count++;
      }
    }

    /**
     * @brief Pops an elemenet from the front of the buffer, throws an error if the buffer is empty
     *
     * @return T - the element that was in the front position
     */
    T pop_front() {
      if(this->empty()) {
        throw std::out_of_range ("pop_front on empty buffer");
      } else {
        this->front = (this->size + this->front - 1) % this->size;
        this->count--;
        return this->buffer[this->front];
      }
    }

    /**
     * @brief Pushes an element to the back of the ringbuffer, drops the element silently if its full
     *
     * @param T - the element that is supposed to be pushed
     */
    void push_back(const T &in) {
      if(!this->full()) {
        this->back = (this->size + this->back - 1) % this->size;
        this->count++;
        this->buffer[this->back] = in;
      }
    }

    /**
     * @brief Pops an elemenet from the back of the buffer, throws error if the buffer is empty
     *
     * @return T - the element that was in the back position
     */
    T pop_back() {
      if(this->empty()) {
        throw std::out_of_range ("pop_back on empty buffer");
      } else {
        int oldBack = this->back;
        this->back = (this->back + 1) % this->size;
        this->count--;
        return this->buffer[oldBack];
      }
    }

    /**
     * @brief Is the buffer empty?
     *
     * @return bool - is empty?
     */
    bool empty() const {
      return this->count == 0;
    }

    /**
     * @brief Is the buffer full?
     *
     * @return bool - is full?
     */
    bool full() const {
      return this->count == this->size;
    }

    /**
     * @brief Simply prints the Buffer
     */
    void print() const {
      if(this->empty()) {
        std::cout << "Buffer is empty" << std::endl;
      } else {
        std::cout << "Content of buffer: ";

        //from front to back, excluding front and including back
        for(int i = 1; i <= this->count; i++) {
          // lots of offsetting
          std::cout << this->buffer[(this->size + this->front - i) % this->size] << '\t';
        }
        std::cout << std::endl;
      }
    }

  private:
    T *buffer;
    int size;
    int front;
    int back;
    int count;
};

#endif
