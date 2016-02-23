// comparing apples with apples
#include <iostream>
#include <string>

bool startsWith(const std::string &str1, const std::string &str2) {
  int ret = str1.compare(0, str2.length(), str2);
  if (ret == 0)
    std::cout << str1 << " startsWith " << str2 << '\n';
  return ret;
  //return (str1.compare(0, str2.length(), str2) == 0);
}

bool endsWith(const std::string &str1, const std::string &str2) {
  try {
    int ret = str1.compare(str1.length()-str2.length(), str2.length(), str2);
    if (ret == 0)
      std::cout << str1 << " endsWith " << str2 << '\n';
    return ret;
  } catch (const std::out_of_range &exc) {
    return false;
  }
}


int main ()
{
  std::string str1("green apple");
  std::string str2("green");
  std::string str3("green apples are blue");
  std::string str4("");
  std::string str5("green apple");

  std::string str6("apple");
  std::string str7("green apple");
  std::string str8("e");
  std::string str9("");
  std::string str10("hey green apple");

  startsWith(str1, str2);
  startsWith(str1, str3);
  startsWith(str1, str4);
  startsWith(str1, str5);

  endsWith(str1, str6);
  endsWith(str1, str7);
  endsWith(str1, str8);
  endsWith(str1, str9);
  endsWith(str1, str10);
  return 0;
}
