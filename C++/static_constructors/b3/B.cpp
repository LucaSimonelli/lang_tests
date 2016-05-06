#include "B.h"
#include <iostream>

const std::unordered_map<int, std::string> & B::getMap() {
  static const std::unordered_map<int, std::string> map = {
    {0, std::string("zero")},
    {1, std::string("one")},
    {2, std::string("two")}
  };
  return map;
}

B myB;

B::B() {
  std::cout << "B::B() B::getMap().at(0)=" << B::getMap().at(0) << std::endl;
}
B::B(const B & other) {
  std::cout << "B::B(const B & other) B::getMap().at(0)=" << B::getMap().at(0) << std::endl;
}
B::B(B && other) {
  std::cout << "B::B(B && other) B::getMap().at(0)=" << B::getMap().at(0) << std::endl;
}



B::~B() {
  std::cout << "B::~B() B::getMap().at(0)=" << B::getMap().at(0) << std::endl;
}


