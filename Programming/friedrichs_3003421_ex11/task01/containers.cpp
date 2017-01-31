#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <utility>
#include <algorithm>

/**
 *
 * @brief Fill the container with even values from 2 - 64
 *
 * @param Cont - container to be filled
 */
template<class Cont>
void fill(Cont &cont) {
  for(int i = 2; i <= 64; i += 2) {
    cont.push_back(i);
  }
}

/**
 *
 * @brief Print the values of the container seperated by spaces
 *
 * @param Cont - container to be printed
 */
template<class Cont>
void print(Cont &cont) {
  for(class Cont::iterator it = cont.begin(); it != cont.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

/**
 *
 * @brief Print the next 3 values starting at the supplied iterator
 *
 * @param Cont - container to be printed
 * @param Cont::iterator - iterator
 */
template<class Cont>
void printnext3(Cont &cont, class Cont::iterator iter) {
  int i = 0;
  do {
    std::cout << *iter++ << " ";
    i++;
  } while(iter != cont.end() && i < 3);
  std::cout << std::endl;
}

/**
 *
 * @brief Find the position of where the value should be inserted
 *
 * @param Cont - container to be printed
 * @param long - value for which to find the position
 *
 * @return std::pair<Cont::iterator, Cont::iterator> - position of the insert and position before it
 */
template<class Cont>
std::pair<class Cont::iterator, class Cont::iterator> findposition(Cont &cont, long val) {
  class Cont::iterator last_it = cont.begin();
  for(class Cont::iterator it = cont.begin(); it != cont.end(); it++) {
    if(*it >= val) {
      return std::pair<class Cont::iterator, class Cont::iterator>(last_it, it);
    }
    last_it = it;
  }
}

/**
 *
 * @brief Deletes all odd values from container
 *
 * @param Cont - container to be un-odded
 */
template<class Cont>
void deleteodd(Cont &cont) {
  cont.erase(std::remove_if(cont.begin(), cont.end(), [](long x){return x % 2 == 1;}), cont.end());
}

/**
 *
 * @brief Tests various iterator actions on a vector, a deque and a list
 *
 */
int main(int argc, char* argv[]) {
  std::vector<long> myvec;
  std::deque<long> mydeq;
  std::list<long> mylist;

  fill(myvec);
  fill(mydeq);
  fill(mylist);

  std::vector<long>::iterator vecit = myvec.begin();
  std::deque<long>::iterator deqit = mydeq.begin();
  std::list<long>::iterator listit = mylist.begin();

  listit++;listit++;listit++;
  std::cout << *(vecit += 3) << std::endl;
  std::cout << *(deqit += 3) << std::endl;
  std::cout << *(listit) << std::endl;

  printnext3(myvec, vecit);
  printnext3(mydeq, deqit);
  printnext3(mylist, listit);

  std::pair<std::vector<long>::iterator, std::vector<long>::iterator> vecpair = findposition(myvec, 31);
  std::pair<std::deque<long>::iterator, std::deque<long>::iterator> deqpair = findposition(mydeq, 31);
  std::pair<std::list<long>::iterator, std::list<long>::iterator> listpair = findposition(mylist, 31);

  // couldve been included in FIX_A but needs to happen before insert and doesnt bother anyone else
  long vecdiff = vecpair.first - myvec.begin();
  long deqdiff = deqpair.first - mydeq.begin();

  std::vector<long>::iterator vecins = myvec.insert(vecpair.second, 1, 31);
  std::deque<long>::iterator deqins = mydeq.insert(deqpair.second, 1, 31);
  std::list<long>::iterator listins = mylist.insert(listpair.second, 1, 31);

  #ifdef FIX_A
    vecpair.first = myvec.begin() + vecdiff;
    deqpair.first = mydeq.begin() + deqdiff;
  #endif

  #ifdef FIX_B
    vecpair.first = --vecins;
    deqpair.first = --deqins;
    listpair.first = --listins;
  #endif

  printnext3(myvec, vecpair.first);
  printnext3(mydeq, deqpair.first);
  printnext3(mylist, listpair.first);

  print(myvec);
  print(mydeq);
  print(mylist);

  deleteodd(myvec);
  deleteodd(mydeq);
  deleteodd(mylist);

  print(myvec);
  print(mydeq);
  print(mylist);

  return 0;
}
