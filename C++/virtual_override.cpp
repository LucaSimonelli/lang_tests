#include <cstdlib>
#include <cstdio>
#include <iostream>

class A {
  public:
    virtual void foo() {
      printf("A::foo\n");
    }
    virtual ~A() { printf("A::~A\n");}
};

class B: public A {
  public:
    void foo() {
      printf("B::foo\n");
    }
    ~B() { printf("B::~B\n");}
};

class C: public B {
  public:
    void foo() {
      printf("C::foo\n");
    }
    ~C() { printf("C::~C\n");}
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

  {
    std::cout << "new B" << std::endl;
    A * ap = new B();
    delete ap;
  }
  std::cout << "deleted B" << std::endl;

  {
    std::cout << "new C" << std::endl;
    A * ap = new C();
    delete ap;
  }
  std::cout << "deleted C" << std::endl;

  {
    std::cout << "new C" << std::endl;
    B * bp = new C();
    delete bp;
  }
  std::cout << "deleted C" << std::endl;


  return 0;
}
