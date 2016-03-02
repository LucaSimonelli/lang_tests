#include <iostream>

class Base {
  public:
  Base() { std::cout << "Base()" << std::endl; }
  virtual ~Base() { std::cout << "~Base()" << std::endl; }
  virtual void handle() { std::cout << "Base::handle()" << std::endl;  }

};

class A : public Base {
  public:
  A(int val) { std::cout << "A() " << val << std::endl; }
  virtual ~A() { std::cout << "~A()" << std::endl; }
  virtual void handle() { std::cout << "A::handle()" << std::endl;  }

};

int main(int argc, char * argv[]) {
  Base * ptrA = new A(2);
  ptrA->handle();
  return 0;
}
