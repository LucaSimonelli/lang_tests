#include <memory>
#include <iostream>

class A {
  public:
    A(): val(10) {}
    ~A() {}
    void  foo() {std::cout << "I'm A" << std::endl;}
  private:
    int val;
};

int main(int argc, char *argv[]) {
  std::shared_ptr<A> ptrA(new A);
  ptrA->foo();
  return 0;
}
