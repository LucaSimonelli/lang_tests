//#include <memory>
#include "my_memory.hpp"
#include <iostream>
#include <vector>

//using std::unique_ptr;
using owesome::unique_ptr;

class A {
  public:
  A(): a(10) { std::cout << "construct A" << std::endl; }
  ~A() { std::cout << "destroy A" << std::endl; }
  void foo() { std::cout << "I'm A" << std::endl; }
  private:
  int a;
};

// unique_ptr for single object
auto makeA() {
  unique_ptr<A> ptrA(nullptr);
  ptrA.reset(new A);
  return ptrA;
}

/*
// unique_ptr for single object
auto makeAWithDelete() {
  auto deleteA = [](A *ptrA) {
    std::cout << "deleteA" << std::endl;
    delete ptrA;
  };
  unique_ptr<A, decltype(deleteA)> ptrA(nullptr, deleteA);
  ptrA.reset(new A);
  return ptrA;
}

// unique_ptr for array, only for literature, never used
// prefer std::vector of unique_ptr
auto makeArrayAWithDelete(int size) {
  auto deleteA = [](A *ptrA) {
    std::cout << "deleteA" << std::endl;
    delete[] ptrA;
  };
  unique_ptr<A[], decltype(deleteA)> ptrA(nullptr, deleteA);
  ptrA.reset(new A[size]);
  return ptrA;
}
*/
int main(int argc, char * args[]) {
  {
    auto ptrA0 = makeA();
  }
  std::cout << "end of test" << std::endl;
  /*
  std::cout << "Allocate single A object" << std::endl;
  auto ptrA = makeAWithDelete();
  ptrA->foo();

  std::cout << "Allocate array of A objects" << std::endl;
  auto ptrArrayA = makeArrayAWithDelete(2);
  ptrArrayA[0].foo();
  std::cout << "Allocate single A object and assign it to a shared_ptr" << std::endl;
  std::shared_ptr<A> ptrA2 = makeA();
  ptrA2->foo();
  */
  std::cout << "Allocate std::vector of A objects" << std::endl;
  std::vector< unique_ptr<A> > aVector;
  //aVector[0] = makeA(); // Error! Segmentation fault!
  aVector.push_back(makeA());
  // error: call to implicitly-deleted copy constructor of unique_ptr
  // you cannot copy a unique_ptr, unless you assign it to a std::shared_ptr
  // auto ptrA2 = ptrA;
  return 0;
}
