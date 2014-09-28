#ifndef PREDEF_H
#define PREDEF_H
#include "Object.h"
#include <list>
#include <map>

#define BCODE 1
#define BLIST 2

class Arbiter;

class PredefData : public Object
{
    public:
        int getType(){return PREDEF_DATA;}
        virtual int getEnum()=0;
        virtual void decCount(){}
    protected:
    private:
};

class BCode : public PredefData{
    public:
        virtual int getEnum(){return BCODE;}
};

class BList : public PredefData{
    public:
        virtual int getEnum(){return BLIST;}
};






class PredefFunc : public Object
{
    public:
        int getType(){return PREDEF_FUNC;}
        virtual void execute(list<Object*> &stack, map<string,Object*> &context)=0;
        virtual void decCount(){}
};

class Print : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class EndList : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class Func : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class Assign : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class Return : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class Done : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class Break : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class Continue : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class True : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class False : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class Add : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class Sub : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class Mul : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class Div : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class Rem : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class Dereference : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class New : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class Greater : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class Less : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class EGreater : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class ELess : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class Equal : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class NEqual : public PredefFunc{
    public:
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
};

class ClassKey : public PredefFunc{
    public:
        ClassKey(Arbiter* a):arb(a){}
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
        Arbiter* arb;
};

class If : public PredefFunc{
    public:
        If(Arbiter* a):arb(a){}
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
        Arbiter* arb;
};

class Ifell : public PredefFunc{
    public:
        Ifell(Arbiter* a):arb(a){}
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
        Arbiter* arb;
};

class While : public PredefFunc{
    public:
        While(Arbiter* a):arb(a){}
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
        Arbiter* arb;
};

class Exec : public PredefFunc{
    public:
        Exec(Arbiter* a):arb(a){}
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
        Arbiter* arb;
};

class Import : public PredefFunc{
    public:
        Import(Arbiter* a):arb(a){}
        virtual void execute(list<Object*> &stack, map<string,Object*> &context);
        Arbiter* arb;
};
#endif // PREDEF_H
