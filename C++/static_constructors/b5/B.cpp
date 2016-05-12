#include "B.h"
#include <iostream>

const std::shared_ptr<std::unordered_map<int, std::string>> & B::getMap() {
  static const std::shared_ptr<std::unordered_map<int, std::string>> map(
    new std::unordered_map<int, std::string> {
      {0, std::string("zero")}
    });
  return map;
}

B myB;

B::B() {
  std::cout << "B::B() B::getMap()->at(0)=" << B::getMap()->at(0) << std::endl;
}

B::B(const B & other) {
  std::cout << "B::B(const B & other) B::getMap()->at(0)=" << B::getMap()->at(0) << std::endl;
}

B::B(B && other) {
  std::cout << "B::B(B && other) B::getMap()->at(0)=" << B::getMap()->at(0) << std::endl;
}

B::~B() {
  std::cout << "B::~B() B::getMap()->at(0)=" << B::getMap()->at(0) << std::endl;
}

