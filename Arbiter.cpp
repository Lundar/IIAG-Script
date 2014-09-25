#include "Arbiter.h"
#include "Predef.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

Arbiter::Arbiter() {

    predef["]"]= new EndList();
    predef["["]= new BList();
    predef["print"]= new Print();
    predef["func"]= new Func();
    predef["class"]= new ClassKey(this);
    predef["return"]= new Return();
    predef["done"]= new Done();
    predef["if"]= new If(this);
    predef["ifell"]= new Ifell(this);
    predef["while"]= new While(this);
    predef["="]= new Assign();
    predef[":"]= new Dereference();
    predef["+"]= new Add();
    predef["-"]= new Sub();
    predef["*"]= new Mul();
    predef["/"]= new Div();
    predef["%"]= new Rem();
    predef["break"]= new Break();
    predef["continue"]= new Continue();
    predef["true"]= new True();
    predef["false"]= new False();
    predef[">"]= new Greater();
    predef["<"]= new Less();
    predef[">="]= new EGreater();
    predef["<="]= new ELess();
    predef["=="]= new Equal();
    predef["!="]= new NEqual();

}

Arbiter::~Arbiter() {
    //dtor
}

void Arbiter::loadFile(string s) {

    ifstream in(s.c_str());
    string code;
    char temp;
    bool quote=false;
    bool esc=false;
    if(in.good())
        temp=in.get();
    while(in.good()) {

        if(temp=='"'&& !esc)
            quote=!quote;

        if(temp =='\\')
            esc=true;
        else
            esc=false;

        if(temp=='['||temp==']'||temp=='{'||temp=='}')
            code = code+" "+temp+" ";
        else
            code = code+temp;

        temp=in.get();
    }

    //cout<<code<<endl;
    list<Object*> newStack;
    executeString(code,newStack,global);

}

void Arbiter::main(){
    if(global.find("main") != global.end()){
        list<Object*> stack;
        executeFunction((Function*)global["main"],stack);
    }else
        cerr<<"no main function found!"<<endl;
}

void Arbiter::executeFunction(Function* f, list<Object*> &stack) {
//cout<<f->getCode()<<" | "<<f->getParam()->length()<<endl;
map<string,Object*> context;
List* param = f->getParam();

for(int x=0;x<param->length();x++){

if(param->at(x)->getType()!= NAME)
continue;


if(!stack.size()){
    cerr<<"not enough args"<<endl;
    return;
}
context[((Name*)param->at(x))->getName()]=stack.back();
stack.pop_back();
}
list<Object*> newStack;
executeString(f->getCode(),newStack,context);

if(context.find("return") != context.end()){
    List *l = (List*)context["return"];
    for(int x=0;x<l->length();x++){
        stack.push_back(l->at(x));
        l->at(x)->incCount();
    }
}

for(map<string,Object*>::iterator it = context.begin(); it != context.end(); it++)
(it)->second->decCount();

}

///TODO check for illegal names
Object* Arbiter::str2Obj(string s, map<string,Object*> &context, bool globe, bool deref) {

if(isdigit(s[0]) || s[0]=='.' || (s[0]=='-' && (isdigit(s[1]) || s[1]=='.'))){
    if(s[s.length()-1]=='i')
        return new Int(atoi(s.substr(0,s.length()-1).c_str()));
    return new Float(atof(s.c_str()));
}

if(s[0]=='('){
deref=true;
s=s.substr(1);
}

string sub="";
if(s.find(".") != string::npos){
    sub= s.substr(s.find(".")+1);
    s=s.substr(0,s.find("."));
    //cout<<s<<" "<<sub<<endl;
}


Object* ret=NULL;//&theNix;
if(globe){
//check for predefs
if(predef.find(s) != predef.end())
    ret= predef[s];

//check global
if(global.find(s) != global.end()){
    global[s]->incCount();
    ret= global[s];
}
}
//check local
if(context.find(s) != context.end()){
    context[s]->incCount();
    ret= context[s];
}


if(ret && ret->getType()==CLASS&& !sub.empty()){

ret = str2Obj(sub,((Class*)ret)->getContext(),false,deref);
//cout<<sub<<"."<<" "<<ret->getType()<<endl;
}

if(!deref)
    if(ret && ret->getType()==NAME){
        ((Name*)ret)->getObj()->incCount();
        ret=((Name*)ret)->getObj();
    }

if(ret==NULL){
    ret= new Name(s);
    context[s]=ret;
}

if(deref)
    if(ret->getType()!=NAME){
        ret->incCount();
        ret=new Name("",ret);
    }


return ret;
}

void Arbiter::executeString(string s,list<Object*> &stack, map<string,Object*> &context) {

    //list<Object*> stack;

    stringstream code(s);
    string temp;
    while(code.good()) {

        if(context.find("done") != context.end())
            break;

        code >> temp;

        if(temp[0]=='"') {

            string str;
            str+= temp;
            while(code.good()) {
                if(temp[temp.length()-1]=='"')
                    break;
                code >> temp;
                str+= " "+temp;
            }
            str=str.substr(1,str.length()-2);
            while(str.find("\\n") != string::npos)
                str.replace(str.find("\\n"),2,"\n");
            stack.push_back(new String(str));

            continue;
        }

        if(temp[0]=='{') {

            int level=1;
            string str;

            while(code.good()) {
                code >> temp;

                if(temp[0]=='{')
                    level++;
                if(temp[0]=='}')
                    level--;
                if(level == 0)
                    break;

                str+= " "+temp;
            }

            stack.push_back(new String(str));

            continue;
        }


        Object *o = str2Obj(temp, context);
        if(o->getType()==FUNC){
            executeFunction((Function*)o,stack);
        } else if(o->getType()==PREDEF_FUNC){
            ((PredefFunc*)o)->execute(stack,context);
        } else {
            o->incCount();
            stack.push_back(o);
        }

    }




}
