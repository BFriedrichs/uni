
#include <iostream>

#include "list.hpp"

/**
 *  @brief List Constructor
 */
template<class T>
List<T>::List() {
  this->first = NULL;
  this->last = NULL;
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

  if(this->last == NULL) {
    this->last = n;
  } else {
    this->first->previous = n;
  }
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
  Node<T> *n = new Node<T>{value, NULL, this->last};

  if(this->first == NULL) {
    this->first = n;
  } else {
    this->last->next = n;
  }
  this->last = n;

  size++;
}

/**
 *  @brief Removes an item from the front of the list and returns it
 *
 *  @return T, item that got deleted
 */
template<class T>
T List<T>::remove_front() {
  T result = NULL;

  if(this->first != NULL) {
    result = this->first->content;

    if(this->first == this->last) {
      delete this->first;
      this->first = this->last = NULL;
    } else {
      this->first = this->first->next;
      delete this->first->previous;
      this->first->previous = NULL;
    }
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

  if(this->first != NULL) {
    result = this->last->content;

    if(this->first == this->last) {
      delete this->first;
      this->first = this->last = NULL;
    } else {
      this->last = this->last->previous;
      delete this->last->next;
      this->last->next = NULL;
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
  return size == 0;
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
  this->first = this->last = NULL;
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
