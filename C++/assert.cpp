#include <iostream>
#include <cassert>

// Even using the -g option, the assert is not included if you compile with the
// -DNDEBUG flag
// g++ -DNDEBUG -g assert.cpp -o assert

int main() {
    assert (1==2);
    return 0;
}
