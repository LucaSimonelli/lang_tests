#include <iostream>
#include <string>

void makeStackDirty(char * t1, char *t2, char *t3, char *t4) {

}

void printMessyString() {
  std::string name = {'A'};
  std::cout << name << std::endl;
}

int main(int argc, char * argv[]) {
  char text[] = "Woo!";
  makeStackDirty(text, text, text, text);
  printMessyString();
  return 0;
}
