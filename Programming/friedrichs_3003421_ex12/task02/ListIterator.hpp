#ifndef EX12_LSTIT_H
#define EX12_LSTIT_H

#include <iostream>
#include <iterator>
#include "node.hpp"

template<class T>
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
private:
  Node<T> *node;
public:
  ListIterator(Node<T> *node) : node(node) {}

  ~ListIterator() { }

  bool operator==(const ListIterator<T> &i) const {
    return this->node == i.node;
  }

  bool operator!=(const ListIterator<T> &i) const {
    return !(this->node == i.node);
  }

  T operator*() {
    return this->node->content;
  }

  ListIterator<T> &operator++() {
    this->node = this->node->next;
    return *this;
  }

  ListIterator<T> &operator--() {
    this->node = this->node->previous;
    return *this;
  }

};

#endif
