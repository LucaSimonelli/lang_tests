#include <iostream>

constexpr int ten_to_the(int n) {
  return (n == 0) ? 1 : 10 * ten_to_the(n - 1);
};

int main(int argc, char *argv[]) {

  constexpr int a = ten_to_the(2);
  constexpr int n = 3; // OK
  // n = 4; // ERROR constexpr objects are const
  //int n = 3; // ERROR the next line would not compile
  constexpr int b = ten_to_the(n);
  printf("a=%d\n", a);
  printf("b=%d\n", b);
  return 0;
}

