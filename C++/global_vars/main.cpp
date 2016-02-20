#include "A.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>

int main() {
    A a1;
    A a2;

    a1.inc();
    a2.inc();
    std::cout << a1.get() << std::endl;
    std::cout << a2.get() << std::endl;
    return 0;
}
