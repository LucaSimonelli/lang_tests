#include "A.h"
#include <iostream>

const std::unordered_map<int, B> A::map = {
  {0, B()},
  {1, B()},
  {2, B()}
};

A::A() {
  std::cout << "A::A()" << std::endl;
}
