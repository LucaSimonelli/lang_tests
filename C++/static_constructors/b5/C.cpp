#include "B.h"
#include "C.h"
#include <iostream>

C myC;

C::C() {
  std::cout << "C::C()" << std::endl;
}

C::C(const C & other) {
  std::cout << "C::C(const C & other)" << std::endl;
}

C::C(C && other) {
  std::cout << "C::C(C && other)" << std::endl;
}

C::~C() {
  std::cout << "C::~C() B::getMap()->at(0)=" << B::getMap()->at(0) << std::endl;
}

