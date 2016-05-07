#pragma once
#include <unordered_map>
#include <memory>

class B {
  public:
  B();
  B(const B & other);
  B(B && other);
  ~B();
  static const std::unique_ptr<std::unordered_map<int, std::string>> & getMap();
};
