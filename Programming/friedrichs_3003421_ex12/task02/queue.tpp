#include <iostream>

#include "queue.hpp"

/**
 *  @brief Queue Constructor
 */
template<class T>
Queue<T>::Queue() {
  this->list = new List<T>;
}

/**
 *  @brief Queue Destructor
 */
template<class T>
Queue<T>::~Queue() {
  delete this->list;
}

/**
 *  @brief Add an item to back of the queue
 *
 *  @param T, item to be added to back
 */
template<class T>
void Queue<T>::add(const T &value) {
  this->list->add(value);
}

/**
 *  @brief Removes an item from the front of the queue and returns it
 *
 *  @return T, item that got deleted
 */
template<class T>
T Queue<T>::remove() {
  return this->list->remove_front();
}

/**
 *  @brief Returns true if queue is empty
 *
 *  @return bool, is the list empty?
 */
template<class T>
bool Queue<T>::isEmpty() {
  return this->list->isEmpty();
}

/**
 *  @brief Checks if the supplied item is already in the queue
 *
 *  @param T, item to be checked
 *  @return bool, item in the queue?
 */
template<class T>
bool Queue<T>::contains(const T &obj) {
  return this->list->contains(obj);
}

/**
 *  @brief Removes every item from the queue
 */
template<class T>
void Queue<T>::clear() {
  this->list->clear();
}

/**
 *  @brief returns size of the queue
 *
 *  @return int, item count
 */
template<class T>
int Queue<T>::getSize() {
  return this->list->getSize();
}

/**
 *  @brief returns an iterator at front of queue
 *
 *  @return QueueIterator
 */
template<class T>
QueueIterator<T> Queue<T>::begin() {
  QueueIterator<T> it(this->list->getFirst());
  return it;
}

/**
 *  @brief returns an iterator at end of queue
 *
 *  @return QueueIterator
 */
template<class T>
QueueIterator<T> Queue<T>::end() {
  QueueIterator<T> it(this->list->getFirst());
  for(int i = 0; i < this->getSize(); ++it, i++);
  return it;
}
