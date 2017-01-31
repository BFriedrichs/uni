#ifndef EX12_COLL_H
#define EX12_COLL_H

template<class T>
class Collection {
public:
  virtual void add(const T &value) = 0;
  virtual T remove() = 0;
  virtual bool isEmpty() = 0;
  virtual bool contains(const T &obj) = 0;
  virtual void clear() = 0;
  virtual int getSize() = 0;
};

#endif
