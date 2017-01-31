#include <iostream>
#include <stdexcept>

#include "ringbuffer.hpp"

int main(void) {
  RingBuffer<int,3> rb;
  rb.print();
  std::cout << std::boolalpha;
  std::cout << "Empty: " << rb.empty() << " Full: " << rb.full() << std::endl;
  rb.push_back(2);
  std::cout << "Empty: " << rb.empty() << " Full: " << rb.full() << std::endl;
  rb.push_front(1);
  rb.push_back(3);
  std::cout << "Empty: " << rb.empty() << " Full: " << rb.full() << std::endl;
  rb.push_back(4);
  std::cout << "Empty: " << rb.empty() << " Full: " << rb.full() << std::endl;
  rb.print();
  std::cout << "pop_front: " << rb.pop_front() << std::endl;
  std::cout << "Empty: " << rb.empty() << " Full: " << rb.full() << std::endl;
  std::cout << "pop_front: " << rb.pop_front() << std::endl;
  rb.push_back(5);
  rb.print();
  std::cout << "pop_back: " << rb.pop_back() << std::endl;
  std::cout << "pop_back: " << rb.pop_back() << std::endl;
  rb.print();
  try {
    rb.pop_back();
    std::cout << "This should not be printed!" << std::endl;
  }
  catch (std::exception& rangeError) {
    std::cout << "Error: " << rangeError.what() << std::endl;
  }
}
