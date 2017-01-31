
#include <iostream>

#include "list.hpp"

/**
 *  @brief List Constructor
 */
template<class T>
List<T>::List() {
  this->first = this->last = new Node<T>{NULL,NULL,NULL};
}

/**
 *  @brief List Destructor
 */
template<class T>
List<T>::~List() {
  this->clear();
}

/**
 *  @brief Add an item to front of the list
 *
 *  @param T, item to be added to front
 */
template<class T>
void List<T>::add_front(const T &value) {
  Node<T> *n = new Node<T>{value, this->first, NULL};

  this->first->previous = n;
  this->first = n;

  size++;
}

/**
 *  @brief Add an item to back of the list
 *
 *  @param T, item to be added to back
 */
template<class T>
void List<T>::add(const T &value) {
  if(this->first == this->last) {
    this->add_front(value);
  } else {
    Node<T> *n = new Node<T>{value, this->last, this->last->previous};

    this->last->previous->next = n;
    this->last->previous = n;

    size++;
  }
}

/**
 *  @brief Removes an item from the front of the list and returns it
 *
 *  @return T, item that got deleted
 */
template<class T>
T List<T>::remove_front() {
  T result = NULL;

  if(this->first != this->last) {
    result = this->first->content;

    this->first = this->first->next;
    delete this->first->previous;
    this->first->previous = NULL;

    size--;
  }

  return result;
}

/**
 *  @brief Removes an item from the back of the list and returns it
 *
 *  @return T, item that got deleted
 */
template<class T>
T List<T>::remove() {
  T result = NULL;

  if(this->first != this->last) {
    result = this->last->previous->content;

    if(this->last->previous == this->first) {
      delete this->last->previous;
      this->first = this->last;
      this->first->previous = NULL;
    } else {
      this->last->previous = this->last->previous->previous;
      delete this->last->previous->next;
      this->last->previous->next = this->last;
    }

    size--;
  }
  return result;
}

/**
 *  @brief Returns true if list is empty
 *
 *  @return bool, is the list empty?
 */
template<class T>
bool List<T>::isEmpty() {
  return this->size == 0;
}

/**
 *  @brief Checks if the supplied item is already in the list
 *
 *  @param T, item to be checked
 *  @return bool, item in the list?
 */
template<class T>
bool List<T>::contains(const T &obj) {
  Node<T> *n = this->first;
  while(n != NULL) {
    if(obj == n->content) {
      return true;
    }
    n = n->next;
  }
  return false;
}

/**
 *  @brief Removes every item from the list
 */
template<class T>
void List<T>::clear() {
  Node<T> *n = this->first;
  while(n != NULL) {
    Node<T> *s = n->next;
    delete n;
    n = s;
  }
  this->first = this->last = new Node<T>{NULL,NULL,NULL};
  size = 0;
}

/**
 *  @brief returns size of the list
 *
 *  @return int, item count
 */
template<class T>
int List<T>::getSize() {
  return size;
}

/**
 *  @brief returns an iterator at front of list
 *
 *  @return ListIterator
 */
template<class T>
ListIterator<T> List<T>::begin() {
  ListIterator<T> it(this->first);
  return it;
}

/**
 *  @brief returns an iterator at end of list
 *
 *  @return ListIterator
 */
template<class T>
ListIterator<T> List<T>::end() {
  ListIterator<T> it(this->last);
  return it;
}
