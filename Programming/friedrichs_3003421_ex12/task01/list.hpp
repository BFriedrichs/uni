#ifndef EX12_LST_H
#define EX12_LST_H

#include <iostream>

#include "collection.hpp"
#include "node.hpp"

template<class T>
class List : public Collection<T> {

private:
  int size = 0;

  Node<T> *first;
  Node<T> *last;

public:
  List();
  ~List();
  void add_front(const T &value);
  virtual void add(const T &value);
  T remove_front();
  virtual T remove();
  virtual bool isEmpty();
  virtual bool contains(const T &obj);
  virtual void clear();
  virtual int getSize();

  /**
   *  @brief add all items (or empty message) to output
   *
   *  @param ostream, stream to write to
   *  @param List, queue to be written
   *  @return ostream, ostream with added message
   */
  friend std::ostream &operator<<(std::ostream &os, const List<T>& obj) {
    Node<T> *n = obj.last;
    if(n == NULL) {
      os << "List is empty!";
    }
    while(n != NULL) {
      os << n->content << " ";
      n = n->previous;
    }
    return os;
  }

};

#include "list.tpp"

#endif
