#include <sstream>
#include <iostream>

int main(int argc, char *argv[]) {
  std::stringstream inOut(std::ios_base::in | std::ios_base::out);
  inOut << "a b c d";
  inOut << " f g h\n";
  inOut.seekg(0, std::ios_base::beg);
  char * buffer = new char[128];
  int readSize = inOut.readsome(buffer, 128);
  std::cout << "readSize = " << readSize << std::endl;
  buffer[readSize+1] = '\0';
  std::cout << buffer << std::endl;
  return 0;
}

