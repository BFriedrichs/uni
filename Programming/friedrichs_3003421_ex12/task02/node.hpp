#ifndef EX12_NODE_H
#define EX12_NODE_H

template<class T>
struct Node {
  T content;
  Node<T> *next;
  Node<T> *previous;

  /**
   *  @brief compare nodes
   *
   *  @param Node, node to be compared
   *  @return bool, is equal
   */
  bool operator==(const Node<T>& obj) const {
    return this->content == obj.content && this->next == obj.next && this->previous == obj.previous;
  }
};

#endif
