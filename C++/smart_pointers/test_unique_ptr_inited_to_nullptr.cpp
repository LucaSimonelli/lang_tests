#include <memory>
#include <cassert>
#include <iostream>

class A {
  public:
    //A(int &&val) : mVal(std::move(val)) {}
    A() {}
    int & getVal() {
      assert(mVal);
      return *mVal;
    }
  private:
    std::unique_ptr<int> mVal;
};

int main(int argc, char *argv[]) {
  //int * val = new int;
  //*val = 100;
  //A aObj(*val);
  A aObj;
  std::cout << aObj.getVal() << std::endl;
  return 0;
}
