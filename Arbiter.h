#ifndef ARBITER_H
#define ARBITER_H
#include "Object.h"
#include <map>
#include <list>
#define for_each(t,x,y) for(t::iterator y = x.begin(); y != x.end(); y++)


using namespace std;

class Arbiter
{
    public:
        Arbiter();
        virtual ~Arbiter();
        void loadFile(string s);
        void executeFunction(Function* f, list<Object*> &stack);
        void main();
    protected:

        void executeString(string s,list<Object*> &stack, map<string,Object*> &context);
        Object* str2Obj(string s, map<string,Object*> &context, bool globe = true, bool deref = false);

    private:

    map<string,Object*> global;
    map<string,Object*> predef;
    list<Object*> data;
    friend class If;
    friend class Ifell;
    friend class While;
    friend class ClassKey;
};

#endif // ARBITER_H
