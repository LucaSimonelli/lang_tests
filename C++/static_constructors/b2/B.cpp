#include "A.h"
#include "B.h"
#include <iostream>
#include <exception>

const std::unordered_map<int, std::string> B::getMap() {
  static const std::unordered_map<int, std::string> map = {
    {0, std::string("zero")},
    {1, std::string("one")},
    {2, std::string("two")}
  };
  return map;
}

B::B() {
  std::cout << "B::B() B::map[0]=" << B::getMap().at(0) << std::endl;
}


