#ifndef EX12_NODE_H
#define EX12_NODE_H

template<class T>
struct Node {
  T content;
  Node<T> *next;
  Node<T> *previous;
};

#endif
