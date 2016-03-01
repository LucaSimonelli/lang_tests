#include <memory>
#include <iostream>
#include <vector>

using std::shared_ptr;
using std::weak_ptr;
using std::unique_ptr;

class A {
  public:
    A(const std::string &id): mId(id) {}
    ~A() {
      std::cout << "~A() " << mId << std::endl;
    }
    void  foo() {std::cout << "I'm A " << mId << std::endl;}
    void setPtr(shared_ptr<A> &ptr) {
      mPtr = ptr;
    }
  private:
    std::string mId;
    weak_ptr<A> mPtr;
};


int main(int argc, char *argv[]) {
  shared_ptr<A> ptrShared1(new A("S1"));
  ptrShared1->foo();
  unique_ptr<A> ptrUnique1(new A("U1"));
  // std::move provides a universal reference of the unique pointer
  shared_ptr<A> ptrShared2(std::move(ptrUnique1));

  std::cout << "Cycle block starting" << std::endl;
  {
    // cycles
    shared_ptr<A> ptrSharedC1(new A("C1"));
    shared_ptr<A> ptrSharedC2(new A("C2"));
    shared_ptr<A> ptrSharedC3(new A("C3"));
    ptrSharedC1->setPtr(ptrSharedC2);
    ptrSharedC2->setPtr(ptrSharedC3);
    ptrSharedC3->setPtr(ptrSharedC1);
    std::vector<shared_ptr<A>> aVector;
    aVector.push_back(ptrSharedC1); ptrSharedC1.reset();
    aVector.push_back(ptrSharedC2); ptrSharedC2.reset();
    aVector.push_back(ptrSharedC3); ptrSharedC3.reset();
  }
  std::cout << "Cycle block exited" << std::endl;
  shared_ptr<A> ptr = nullptr;
  if (ptr != NULL) {
    ptr->foo();
  } else {
    std::cout << "You got a NULL share_ptr" << std::endl;
  }
  return 0;
}
