#include "A.h"
#include "B.h"
#include <iostream>
#include <exception>

const std::unordered_map<int, std::string> B::map = {
  {0, std::string("zero")},
  {1, std::string("one")},
  {2, std::string("two")}
};

B::B() {
  //const auto & it = map.find(0);
  //if (it == map.end()) {
  //  throw std::exception();
  //}
  std::cout << "B::B() B::map[0]=" << B::map.at(0) << std::endl;
}


