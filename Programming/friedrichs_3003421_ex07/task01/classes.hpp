#include <iostream>

#ifndef CLASS_H
#define CLASS_H

class StaticBase {
  public:
    static int myInt;
    static void myFunc();
};

class PureBase {
  public:
    PureBase();
    void myFunc();

  private:
    int myInt;
};

class VirtBase {
  public:
    VirtBase();
    void nvFunc();
    virtual void virtFunc();
    int myInt;
};

class VirtDer : public VirtBase {
  public:
    void myFunc();
    virtual void virtFunc();
    int myInt;
};

#endif
