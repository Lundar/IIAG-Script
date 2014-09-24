#include "Object.h"

Nix theNix;

Object::Object() {
    refCount =1;
}

Object::~Object() {
    //dtor
}

void Object::incCount(){
    refCount++;
}

void Object::decCount(){
    if(!(--refCount))
    delete this;
}

Function::Function(string c, List &p):params(p) {
    code=c;

    for(int x=0;x<p.length();x++)
        p.at(x)->incCount();


}

Function::~Function() {
    //dtor
}

string Function::getCode() {
    return code;
}

int Function::getType() {
    return FUNC;
}

List* Function::getParam(){
    return &params;
}

List::List() {
    //ctor
}

List::~List() {

    for(int x=0;x<data.size();x++)
    data[x]->decCount();

}

int List::getType() {
    return LIST;
}

void List::add(Object* o) {
    data.push_back(o);
}

int List::length() {
    return data.size();
}

Object* List::at(int x) {
    if(x<0|| x>=data.size()) {
        cerr<<"List out of bounds exception "<<x<<endl;
        return &theNix;
    }


    return data.at(x);
}

String::String(string c) {
    str=c;
}

String::~String() {
    //dtor
}

string String::getString() {
    return str;
}

int String::getType() {
    return STRING;
}

int Nix::getType() {
    return NIX;
}

Name::Name(string c) {
    str=c;
    o=&theNix;
    //set=false;
}

Name::Name(string c,Object* ob) {
    str=c;
    o=ob;
    //set=false;
}

Name::~Name() {
    o->decCount();
}

string Name::getName() {
    return str;
}

void Name::setObj(Object * o) {
    this->o=o;
    //set=true;
}

Object* Name::getObj() {
    return o;
}

int Name::getType() {
    return NAME;
}

/*bool Name::isSet() {
    return set;
}*/

Int::Int(int c) {
    n=c;
}

int Int::getValue() {
    return n;
}

int Int::getType() {
    return INT;
}

Float::Float(float c) {
    n=c;
}

float Float::getValue() {
    return n;
}

int Float::getType() {
    return FLOAT;
}

Class::Class() {
}

Class::~Class() {
}

map<string,Object*>& Class::getContext() {
    return context;
}

int Class::getType() {
    return CLASS;
}
