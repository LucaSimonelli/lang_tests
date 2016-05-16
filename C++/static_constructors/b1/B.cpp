#include "A.h"
#include "B.h"
#include <iostream>

const std::unordered_map<int, std::string> B::mMap = {
  {0, std::string("zero")}
};

B::B() {
  std::cout << "B::B() B::mMap.at(0)=" << B::mMap.at(0) << std::endl;
}

