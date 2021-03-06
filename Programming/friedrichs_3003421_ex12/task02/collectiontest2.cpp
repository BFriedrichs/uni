#include "list.hpp"
#include "queue.hpp"
#include <iostream>
#include <algorithm>

int main(void) {
  std::cout << "--- Test List ---" << std::endl;
  List<int> l;
  std::cout << l;
  l.add(2);
  l.add_front(3);
  l.add(1);
  std::cout << l;
  
  std::cout << "remove_front: " << l.remove_front() << std::endl;
  std::cout << "remove_front: " << l.remove_front() << std::endl;
  l.add(5);
  std::cout << l;
  std::cout << "Contains 5? " << l.contains(5) << std::endl;
  
  std::cout << "remove_back: " << l.remove() << std::endl;
  //std::cout << l.remove() << std::endl;
  std::cout << "remove_back: " << l.remove() << std::endl;
  std::cout << l;
  
  std::cout << std::endl << "--- Test Queue ---" << std::endl;
  Queue<int> q;
  std::cout << q;
  q.add(1);
  q.add(2);
  q.add(3);
  std::cout << q;
  
  std::cout << "remove_front: " << q.remove() << std::endl;
  std::cout << "remove_front: " << q.remove() << std::endl;
  q.add(4);
  std::cout << q;
  std::cout << "Contains 3? " << q.contains(3) << std::endl;
  std::cout << "Contains 5? " << q.contains(5) << std::endl;
  q.clear();
  std::cout << q;
  
  std::cout << std::endl << "--- Test List Iterator ---" << std::endl;
  List<int> l2;  
  std::cout << l2;
  l2.add(5);
  l2.add_front(4);
  l2.add(6);
  std::cout << l2;
  //std::sort(l2.begin(), l2.end());
  
  std::cout << "Content at begin: " << *(l2.begin()) << " done" << std::endl;
  std::copy(l2.begin(), l2.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  return 0;
}
