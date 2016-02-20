#include "A.h"

// Not necessary to init static globals to 0 or NULL
// as they get initialised automatically
// static int a = 0;
static int a;

int A::get() {return a;}
int A::inc() { return ++a; }
