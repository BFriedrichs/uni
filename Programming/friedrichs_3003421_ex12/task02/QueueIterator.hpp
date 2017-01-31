#ifndef EX12_QUEIT_H
#define EX12_QUEIT_H

#include <iostream>
#include <iterator>
#include "node.hpp"

template<class T>
class QueueIterator : public std::iterator<std::forward_iterator_tag, T> {
private:
  Node<T> *node;
public:
  QueueIterator(Node<T> *node) : node(node) {}

  ~QueueIterator() { }

  bool operator==(const QueueIterator<T> &i) const {
    return this->node == i.node;
  }

  bool operator!=(const QueueIterator<T> &i) const {
    return !(this->node == i.node);
  }

  T operator*() {
    return this->node->content;
  }

  QueueIterator<T> &operator++() {
    this->node = this->node->next;
    return *this;
  }

};

#endif
