#include <cstdlib>
#include <string>
#include <iostream>

int main(int argc, char * argv[]) {
  std::string str = "abc";
  std::string::iterator it = str.begin();

  for (int i = 0; i < 20; ++i) {
    std::cout << "#" << *it << "#" << std::endl;
    ++it;
  }
  /*
  std::cout << *it << std::endl; ++it; // a
  std::cout << *it << std::endl; ++it; // b
  std::cout << *it << std::endl; ++it; // c
  std::cout << *it << std::endl; ++it; // out of bounds
  */
  return 0;
}
