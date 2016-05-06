#pragma once
#include <unordered_map>

class C {
  public:
  C();
  C(const C & other);
  C(C && other);
  ~C();
};
