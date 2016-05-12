#pragma once
#include <unordered_map>

class B;

class A {
  public:
  A();
  static const std::unordered_map<int,B> mMap;
};
