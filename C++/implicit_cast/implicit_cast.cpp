#include <iostream>
#include <cstdint>

void foo(float val) {
  val = 1;
}

void foo2(int32_t val) {
  val = 1;
}

int main(int argc, char * argv[]) {
  int32_t val = 0;
  float val2 = 0;
  foo(val);
  foo2(val2);
  return 0;
}
