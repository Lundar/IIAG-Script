#include <iostream>
#include "Arbiter.h"
using namespace std;

int main(int argc, char** argv )
{
    if(argc != 2)
    cout<<"Usage iiasl file"<<endl;
    Arbiter a;
    a.loadFile(string(argv[1]));
    a.main();
}
