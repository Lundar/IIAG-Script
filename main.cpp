#include <iostream>
#include "Arbiter.h"
using namespace std;

int main()
{
    Arbiter a;
    a.loadFile("test.iiag");
    a.main();
}
