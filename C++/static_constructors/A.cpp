#include "A.h"
#include "B.h"
#include <iostream>

const std::unordered_map<int, B> A::mMap = {
  {0, B()}
};

A::A() {
  std::cout << "A::A()" << std::endl;
}
