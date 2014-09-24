#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>
#include <vector>
#include <map>

#define FUNC 1
#define LIST 2
#define PREDEF_DATA 3
#define PREDEF_FUNC 4
#define STRING 5
#define NAME 6
#define NIX 7
#define INT 8
#define FLOAT 9
#define CLASS 10

using namespace std;

class Object
{
    public:
        Object();
        virtual ~Object();
        virtual int getType()=0;

        virtual void incCount();
        virtual void decCount();

    protected:
    private:

    int refCount;

};

class List: public Object{

    public:
        List();
        virtual ~List();
        virtual int getType();
        int length();
        Object* at(int);
        void add(Object* o);

    private:

        vector<Object*> data;

};

class Function: public Object{

    public:
        Function(string c, List &param);
        virtual ~Function();
        virtual int getType();
        string getCode();
        List* getParam();

    private:

        string code;
        List params;

};

class String: public Object{

    public:
        String(string c);
        virtual ~String();
        virtual int getType();
        string getString();

    private:
        string str;

};

class Name: public Object{

    public:
        Name(string c);
        Name(string c,Object* ob);
        virtual ~Name();
        virtual int getType();
        string getName();
        void setObj(Object*);
        Object* getObj();
        //bool isSet();
    private:
        string str;
        Object* o;
        //bool set;
};

class Nix: public Object{
    public:
        virtual int getType();
        virtual void decCount(){}
};

extern Nix theNix;

class Int: public Object{
    public:
        Int(int n);
        virtual int getType();
        int getValue();
    private:
        int n;
};

class Float: public Object{
    public:
        Float(float n);
        virtual int getType();
        float getValue();
    private:
        float n;
};

class Class: public Object{
    public:
        Class();
        virtual ~Class();
        virtual int getType();
        map<string,Object*>& getContext();
    private:
        map<string,Object*> context;
};

#endif // OBJECT_H
