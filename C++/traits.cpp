#include <iostream>

template<typename T1, typename T2>
class A {
  public:
    T1 val;
    T2 val2;
};

template<typename T2>
class B {
  public:
    template <typename U> using C = A<U, U>;
    T2 val2;
    //using my_trait = A<>;
};



int main(int argc, char *argv[]) {
  //typedef template <typename T1> class A D;
  //using C = A;
  A<int, int> a;
  //D<int> d;
  B<int>::C<int> c;
  return 0;
}
