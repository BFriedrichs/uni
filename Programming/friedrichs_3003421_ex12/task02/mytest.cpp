#include "list.hpp"
#include "queue.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

int main(void) {
  std::cout << std::endl << "--- Test Vector Iterator ---" << std::endl;
  std::vector<int> v2;
  v2.push_back(4);
  v2.push_back(5);
  v2.push_back(6);
  //std::sort(l2.begin(), l2.end());

  std::cout << "Content at begin: " << *(v2.begin()) << " " << *(v2.end()) << " done" << std::endl;
  std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::cout << std::endl << "--- Test List Iterator ---" << std::endl;
  List<int> l2;
  std::cout << l2;
  l2.add(5);
  l2.add_front(4);
  l2.add(6);
  std::cout << l2;
  //std::sort(l2.begin(), l2.end());

  std::cout << "Content at begin: " << *(l2.begin()) << " " << *(l2.end()) << " done" << std::endl;
  std::copy(l2.begin(), l2.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;


  std::cout << std::endl << "--- Test Queue Iterator ---" << std::endl;
  Queue<int> q2;
  std::cout << q2;
  q2.add(4);
  q2.add(5);
  q2.add(6);
  std::cout << q2;
  //std::sort(l2.begin(), l2.end());

  std::cout << "Content at begin: " << *(q2.begin()) << " " << *(q2.end()) << " done" << std::endl;
  std::copy(q2.begin(), q2.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  return 0;
}
