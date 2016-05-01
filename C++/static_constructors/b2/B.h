#pragma once
#include <unordered_map>

//extern class B b;

class B {
  public:
  B();
  static const std::unordered_map<int, std::string> getMap();
};
