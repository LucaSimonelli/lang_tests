#pragma once
#include <unordered_map>
#include "B.h"


class A {
  public:
  A();
  static const std::unordered_map<int,B> map;
};
