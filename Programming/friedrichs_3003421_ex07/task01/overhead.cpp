#include <iostream>
#include <typeinfo>
#include "stopwatch.hpp"
#include "classes.hpp"

#define MEASURETIME(description, repetitions, instructions2test) {              \
                _W.start();                                                     \
                for(int _ITER = 0; _ITER < repetitions; _ITER++) {              \
                    instructions2test;                                          \
                }                                                               \
                std::cout << "My computer requires ";                           \
                std::cout << _W.stop() << " ";                                  \
                std::cout << "seconds to execute ";                             \
                std::cout << description << " ";                                \
                std::cout << repetitions << " ";                                \
                std::cout << "times" << std::endl; }

int main() {
  PureBase pure;
  VirtBase vbase;
  VirtDer vder;
  PureBase *ppure = new PureBase();
  VirtBase *pvbase = new VirtBase();
  VirtDer *pvder = new VirtDer();
  VirtBase *pvbaseder = pvder;

  // Static member function
  StaticBase::myFunc();

  // Non virtual member function
  pure.myFunc();
  ppure->myFunc();
  vbase.nvFunc();
  pvbase->nvFunc();
  vder.myFunc();
  pvder->myFunc();
  vder.nvFunc();
  pvder->nvFunc();
  pvbaseder->nvFunc();

  // virtual member w/ vtable lookup
  vder.virtFunc();
  pvder->virtFunc();
  vbase.virtFunc();
  pvbase->virtFunc();
  pvbaseder->virtFunc();

  #ifdef TASK02
    StopWatch _W;

    MEASURETIME("StaticBase::myFunc()", 50000000, StaticBase::myFunc())
    MEASURETIME("pure.myFunc()", 50000000, pure.myFunc())
    MEASURETIME("ppure->myFunc()", 50000000, ppure->myFunc())
    MEASURETIME("vbase.nvFunc()", 50000000, vbase.nvFunc())
    MEASURETIME("pvbase->nvFunc()", 50000000, pvbase->nvFunc())
    MEASURETIME("vder.myFunc()", 50000000, vder.myFunc())
    MEASURETIME("pvder->myFunc()", 50000000, pvder->myFunc())
    MEASURETIME("vder.nvFunc()", 50000000, vder.nvFunc())
    MEASURETIME("pvder->nvFunc()", 50000000, pvder->nvFunc())
    MEASURETIME("pvbaseder->nvFunc()", 50000000, pvbaseder->nvFunc())

    MEASURETIME("vder.virtFunc()", 50000000, vder.virtFunc())
    MEASURETIME("pvder->virtFunc()", 50000000, pvder->virtFunc())
    MEASURETIME("vbase.virtFunc()", 50000000, vbase.virtFunc())
    MEASURETIME("pvbase->virtFunc()", 50000000, pvbase->virtFunc())

    MEASURETIME("pvbaseder->virtFunc()", 50000000, pvbaseder->virtFunc())
  #endif

  #ifdef TASK03
    StopWatch _W;
    MEASURETIME("dynamic_cast", 50000000,  {
      if(VirtDer *der = dynamic_cast<VirtDer *>(pvbaseder)) {
          der->myFunc();
      }
    })
    MEASURETIME("cast", 50000000, {
      VirtDer *der = (VirtDer *) pvbaseder;
      if(typeid(der) == typeid(VirtDer *)) {
        der->myFunc();
      }
    })
  #endif

  return 0;
}
