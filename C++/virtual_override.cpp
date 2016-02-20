#include <cstdlib>
#include <cstdio>
#include <iostream>

class A {
  public:
    virtual void foo() {
      printf("A::foo\n");
    }
};

class B: public A {
  public:
    void foo() {
      printf("B::foo\n");
    }
};

class C: public B {
  public:
    void foo() {
      printf("C::foo\n");
    }
};

int main(int argc, char * argv[]) {
  A a;
  B b;
  C c;

  a.foo();
  b.foo();
  c.foo();
  std::cout << std::endl;
  A * ptrA2B = &b;
  A * ptrA2C = &c;
  ptrA2B->foo();
  ptrA2C->foo();
  B * ptrB2C = &c; // still behaves as virtual
  ptrB2C->foo();
  return 0;
}
