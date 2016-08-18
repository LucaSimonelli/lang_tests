#include <iostream>
#include <memory>

/*
This will fail at compile time with:
copy_constructor_on_unique_ptr.cpp:30:7: error: call to implicitly-deleted copy constructor of 'A'
  foo(aObj);
      ^~~~
copy_constructor_on_unique_ptr.cpp:16:26: note: copy constructor of 'A' is implicitly deleted because field 'mIntUniquePtr' has a deleted copy
      constructor
    std::unique_ptr<int> mIntUniquePtr;

The failure would not happen if the A object provided to foo() was a temporary object. In that case
the copyconstruction will be elided as a compiler optimization. But still you cannot explicitly
delete the copy constructor, in that case it will complain.
*/
class A {
  public:
    A(int *intPtr): mIntPtr(intPtr) {}
    void copyPtr() {
      mIntUniquePtr = std::make_unique<int>(*mIntPtr);
      mIntPtr = mIntUniquePtr.get();
    }
    void dump() {
      std::cout << *mIntPtr << std::endl;
    }
  private:
    int *mIntPtr;
    std::unique_ptr<int> mIntUniquePtr;
};

void foo(A aObj) {
  (void)aObj;
}

int main(int argc, char *argv[]) {
  int *intPtr = new int;
  *intPtr = 12000;

  A aObj(intPtr);
  aObj.copyPtr();
  aObj.dump();
  foo(aObj);
  aObj.dump();
  return 0;
}
