#ifndef EX12_QU_H
#define EX12_QU_H

#include <iostream>

#include "collection.hpp"
#include "list.hpp"
#include "node.hpp"

template<class T>
class Queue : public Collection<T> {
private:
  List<T> *list;

public:
  Queue();
  ~Queue();
  virtual void add(const T &value);
  virtual T remove();
  virtual bool isEmpty();
  virtual bool contains(const T &obj);
  virtual void clear();
  virtual int getSize();

  /**
   *  @brief add all items (or empty message) to output
   *
   *  @param ostream, stream to write to
   *  @param Queue, queue to be written
   *  @return ostream, ostream with added message
   */
  friend std::ostream &operator<<(std::ostream &os, Queue<T>& obj) {
    /*
    * I don't know in what world we ever want to do it like this
    * But since we can't add public functions or declare this class or method as a friend,
    * we have to do it really inefficiently
    */
    List<T> *newList = new List<T>;
    T item = obj.list->remove_front();

    if(item == NULL) {
      os << "Queue is empty!";
    }

    while(item != NULL) {
      newList->add(item);
      os << item << " ";
      item = obj.list->remove_front();
    }
    delete obj.list;
    obj.list = newList;

    return os;
  }
};

#include "queue.tpp"

#endif
