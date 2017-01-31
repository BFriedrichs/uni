#include "classes.hpp"

int StaticBase::myInt = 0;

void StaticBase::myFunc() {
  #ifdef VERBOSE
    std::cout << "Called " << "StaticBase::"
    << __func__ << std::endl;
  #endif

  StaticBase::myInt++;
}

PureBase::PureBase() : myInt(0) { }

void PureBase::myFunc() {
  #ifdef VERBOSE
    std::cout << "Called " << typeid(*this).name() << "::"
    << __func__ << std::endl;
  #endif

  this->myInt++;
}

VirtBase::VirtBase() : myInt(0) { }

void VirtBase::nvFunc() {
  #ifdef VERBOSE
    std::cout << "Called " << typeid(*this).name() << "::"
    << __func__ << std::endl;
  #endif

  this->myInt++;
}

void VirtBase::virtFunc() {
  #ifdef VERBOSE
    std::cout << "Called " << typeid(*this).name() << "::"
    << __func__ << std::endl;
  #endif

  this->myInt++;
}

void VirtDer::myFunc() {
  #ifdef VERBOSE
    std::cout << "Called " << typeid(*this).name() << "::"
    << __func__ << std::endl;
  #endif

  this->myInt++;
}

void VirtDer::virtFunc() {
  #ifdef VERBOSE
    std::cout << "Called " << typeid(*this).name() << "::"
    << __func__ << std::endl;
  #endif

  this->myInt++;
}
