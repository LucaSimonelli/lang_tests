#include <iostream>

class A {
  public:
    virtual int get() {
      std::cout << "A::get()" << std::endl;
      return mVal;
    }
    virtual void set(int val) {
      std::cout << "A::set()" << std::endl;
      mVal=val;
    }
  protected:
    int mVal;
};

class B : public A {
  public:
    virtual int get() {
      std::cout << "B::get()" << std::endl;
      return mVal;
    }
    virtual void set(int val) {
      std::cout << "B::set()" << std::endl;
      mVal=val;
    }
};

int main(int argc, char * argv[]) {
  //A * aa1 = new A;
  A * ab1 = new B;
  B * bb1 = dynamic_cast<B*>(ab1);
  bb1->get();
  B *pb = new B;
  B &rb = *pb;
  A &ra = rb;
  B &rb2 = dynamic_cast<B&>(ra);
  return 0;
}
