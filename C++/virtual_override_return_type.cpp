#include <cstdlib>
#include <cstdio>
#include <iostream>

class A {
  public:
    virtual int foo() {
      printf("A::foo\n");
      return 1;
    }
    virtual ~A() { printf("A::~A\n");}
};

class B: public A {
  public:
    std::string foo() {
      printf("B::foo\n");
      return "one";
    }
    ~B() { printf("B::~B\n");}
};

int main(int argc, char * argv[]) {
  A a;
  B b;
  a.foo();
  b.foo();
  std::cout << std::endl;
  A * ptrA2B = &b;
  ptrA2B->foo();

  return 0;
}
