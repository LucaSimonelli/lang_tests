#include "A.h"
#include <iostream>

const std::unordered_map<int, B> A::map = {
  {0, B()}
};

A::A() {
  std::cout << "A::A()" << std::endl;
}
