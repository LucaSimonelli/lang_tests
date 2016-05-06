#pragma once
#include <unordered_map>

class B {
  public:
  B();
  B(const B & other);
  B(B && other);
  ~B();
  static const std::unordered_map<int, std::string> & getMap();
};
