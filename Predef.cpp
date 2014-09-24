#include "Predef.h"
#include "Arbiter.h"

void printObject(Object* o){

if(o->getType() == STRING)
cout<<((String*)o)->getString();

else if(o->getType() == INT)
cout<<((Int*)o)->getValue();

else if(o->getType() == FLOAT)
cout<<((Float*)o)->getValue();

else if(o->getType() == NIX)
cout<<"NIX";

else if(o->getType() == LIST){
List* l=(List*)o;
    if(l->length()>0)
    printObject(l->at(l->length()-1));

    for(int x=l->length()-2;x>=0;x--){
        cout<<" ";
        printObject(l->at(x));
    }
}

}

void Print::execute(list<Object*> &stack, map<string,Object*> &context){
if(stack.size()< 1){
cerr<<"not enough args!"<<endl;
return;
}
Object * str = stack.back();
stack.pop_back();

printObject(str);

str->decCount();
}

void EndList::execute(list<Object*> &stack, map<string,Object*> &context){
    List * l= new List();
    while(42){
        if(!stack.size()){
            cerr<<"Error endless list"<<endl;
            stack.push_back(l);
            return;
        }

        Object* o=stack.back();
        stack.pop_back();
        if(o->getType()==PREDEF_DATA && ((PredefData*)o)->getEnum() == BLIST){
            stack.push_back(l);
            return;
        }
        //cout<<o->getType()<<endl;
        l->add(o);
    }
}

void Func::execute(list<Object*> &stack, map<string,Object*> &context){

if(stack.size()< 3){
cerr<<"not enough args!"<<endl;
return;
}

Object * name;
Object * li;
Object * code;

name = stack.back();
stack.pop_back();
li = stack.back();
stack.pop_back();
code = stack.back();
stack.pop_back();

if(name->getType() != NAME || li->getType() != LIST || code->getType() != STRING){
cerr<<"Argument mismatch exception"<<endl;
return;
}

context[((Name*)name)->getName()]=new Function(((String*)code)->getString(),*(List*)li);

name->decCount();
li->decCount();
code->decCount();

}

void ClassKey::execute(list<Object*> &stack, map<string,Object*> &context){

if(stack.size()< 3){
cerr<<"not enough args!"<<endl;
return;
}

Object * name;
Object * code;
//Object * li;

name = stack.back();
stack.pop_back();
code = stack.back();
stack.pop_back();
//li = stack.back();
//stack.pop_back();

if(name->getType() != NAME || /*li->getType() != LIST ||*/code->getType() != STRING){
cerr<<"Argument mismatch exception"<<endl;
return;
}

Class* cl= new Class();

/*List* l=(List*)li;
for(int x=0;x<l->length();x++){
if(l->at(x)->getType() == NAME){
    l->at(x)->incCount();
    ((Name*)l->at(x))->setObj(&theNix);
    cl->getContext()[((Name*)l->at(x))->getName()]=l->at(x);
} else
cerr<<"This is not a name!"<<endl;

}*/

context["this"]=cl;

arb->executeString(((String*)code)->getString(),stack,context);

context[((Name*)name)->getName()]=cl;
context.erase("this");

//for(map<string,Object*>::iterator it = cl->getContext().begin(); it != cl->getContext().end(); it++)
//    cout<<it->first<<((Name*)it->second)->getObj()->getType()<<endl;



name->decCount();
code->decCount();
}

void Assign::execute(list<Object*> &stack, map<string,Object*> &context){
if(stack.size()< 2){
cerr<<"not enough args!"<<endl;
return;
}

Object* name;
Object* obj;

name = stack.back();
stack.pop_back();
obj = stack.back();
stack.pop_back();

if(name->getType() != NAME){
cerr<<"argument mismatch error"<<endl;
return;
}

//if(!((Name*)name)->isSet())
//    context[((Name*)name)->getName()]=name;

//cout<<((Name*)name)->getName()<<" = "<<obj->getType()<<endl;
((Name*)name)->setObj(obj);


}

void Dereference::execute(list<Object*> &stack, map<string,Object*> &context){
if(stack.size()< 1){
cerr<<"not enough args!"<<endl;
return;
}

Object* name;

name = stack.back();
stack.pop_back();

if(name->getType() != NAME){
cerr<<"argument mismatch error"<<endl;
return;
}

Object* o=((Name*)name)->getObj();
o->incCount();
stack.push_back(o);

}

void New::execute(list<Object*> &stack, map<string,Object*> &context){
if(stack.size()< 1){
cerr<<"not enough args!"<<endl;
return;
}

Object* obj;

obj = stack.back();
stack.pop_back();


stack.push_back(o);
}

void Return::execute(list<Object*> &stack, map<string,Object*> &context){
if(stack.size()< 1){
cerr<<"not enough args!"<<endl;
return;
}

Object* obj;

obj = stack.back();
stack.pop_back();

if(context.find("return") == context.end())
    context["return"]=new List();

    List *l = (List*)context["return"];
    l->add(obj);

}

void Done::execute(list<Object*> &stack, map<string,Object*> &context){
context["done"]=&theNix;
}

void Break::execute(list<Object*> &stack, map<string,Object*> &context){
context["done"]=new Float(0);
}

void Continue::execute(list<Object*> &stack, map<string,Object*> &context){
context["done"]=new Int(0);
}

void True::execute(list<Object*> &stack, map<string,Object*> &context){
stack.push_back(new Int(1));
}

void False::execute(list<Object*> &stack, map<string,Object*> &context){
stack.push_back(new Int(0));
}

void Add::execute(list<Object*> &stack, map<string,Object*> &context){
if(stack.size()< 2){
cerr<<"not enough args!"<<endl;
return;
}
Object * n1 = stack.back();
stack.pop_back();
Object * n2 = stack.back();
stack.pop_back();

if(n1->getType() == INT && n2->getType() == INT)
    stack.push_back(new Int(((Int*)n1)->getValue()+((Int*)n2)->getValue()));
else{

    float f1=0,f2=0;
    if(n1->getType() == INT)
        f1=((Int*)n1)->getValue();
    else if (n1->getType() == FLOAT)
        f1=((Float*)n1)->getValue();
    if(n2->getType() == INT)
        f2=((Int*)n2)->getValue();
    else if (n2->getType() == FLOAT)
        f2=((Float*)n2)->getValue();

    stack.push_back(new Float(f1+f2));
}

n1->decCount();
n2->decCount();
}

void Sub::execute(list<Object*> &stack, map<string,Object*> &context){
if(stack.size()< 2){
cerr<<"not enough args!"<<endl;
return;
}
Object * n1 = stack.back();
stack.pop_back();
Object * n2 = stack.back();
stack.pop_back();

if(n1->getType() == INT && n2->getType() == INT)
    stack.push_back(new Int(((Int*)n2)->getValue()-((Int*)n1)->getValue()));
else{

    float f1=0,f2=0;
    if(n1->getType() == INT)
        f1=((Int*)n1)->getValue();
    else if (n1->getType() == FLOAT)
        f1=((Float*)n1)->getValue();
    if(n2->getType() == INT)
        f2=((Int*)n2)->getValue();
    else if (n2->getType() == FLOAT)
        f2=((Float*)n2)->getValue();

    stack.push_back(new Float(f2-f1));
}

n1->decCount();
n2->decCount();
}

void Mul::execute(list<Object*> &stack, map<string,Object*> &context){
if(stack.size()< 2){
cerr<<"not enough args!"<<endl;
return;
}
Object * n1 = stack.back();
stack.pop_back();
Object * n2 = stack.back();
stack.pop_back();

if(n1->getType() == INT && n2->getType() == INT)
    stack.push_back(new Int(((Int*)n1)->getValue()*((Int*)n2)->getValue()));
else{

    float f1=0,f2=0;
    if(n1->getType() == INT)
        f1=((Int*)n1)->getValue();
    else if (n1->getType() == FLOAT)
        f1=((Float*)n1)->getValue();
    if(n2->getType() == INT)
        f2=((Int*)n2)->getValue();
    else if (n2->getType() == FLOAT)
        f2=((Float*)n2)->getValue();

    stack.push_back(new Float(f1*f2));
}

n1->decCount();
n2->decCount();
}

void Div::execute(list<Object*> &stack, map<string,Object*> &context){
if(stack.size()< 2){
cerr<<"not enough args!"<<endl;
return;
}
Object * n1 = stack.back();
stack.pop_back();
Object * n2 = stack.back();
stack.pop_back();

if(n1->getType() == INT && n2->getType() == INT)
    stack.push_back(new Int(((Int*)n2)->getValue()/((Int*)n1)->getValue()));
else{

    float f1=0,f2=0;
    if(n1->getType() == INT)
        f1=((Int*)n1)->getValue();
    else if (n1->getType() == FLOAT)
        f1=((Float*)n1)->getValue();
    if(n2->getType() == INT)
        f2=((Int*)n2)->getValue();
    else if (n2->getType() == FLOAT)
        f2=((Float*)n2)->getValue();

    stack.push_back(new Float(f2/f1));
}

n1->decCount();
n2->decCount();
}

void Rem::execute(list<Object*> &stack, map<string,Object*> &context){
if(stack.size()< 2){
cerr<<"not enough args!"<<endl;
return;
}
Object * n1 = stack.back();
stack.pop_back();
Object * n2 = stack.back();
stack.pop_back();

if(n1->getType() == INT && n2->getType() == INT)
    stack.push_back(new Int(((Int*)n2)->getValue()%((Int*)n1)->getValue()));
else{

    cerr<<"can't % floats!"<<endl;
}

n1->decCount();
n2->decCount();
}

bool obj2Bool(Object* o){
bool b = true;
    if(o->getType() == INT)
        b = ((Int*)o)->getValue();
    if(o->getType() == FLOAT)
        b = ((Float*)o)->getValue();

return b;
}


void If::execute(list<Object*> &stack, map<string,Object*> &context){
if(stack.size()< 2){
cerr<<"not enough args!"<<endl;
return;
}
Object * pred = stack.back();
stack.pop_back();
Object * code = stack.back();
stack.pop_back();

if(pred->getType() != STRING || code->getType() != STRING){
    cerr<<"Argument mismatch exception"<<endl;
    return;
}

    list<Object*> newStack;
    arb->executeString(((String*)pred)->getString(),newStack,context);

    if(!newStack.size())
        return;

    Object* t = newStack.back();


    if(obj2Bool(t))
        arb->executeString(((String*)code)->getString(),stack,context);
}

void Ifell::execute(list<Object*> &stack, map<string,Object*> &context){
if(stack.size()< 3){
cerr<<"not enough args!"<<endl;
return;
}
Object * pred = stack.back();
stack.pop_back();
Object * code = stack.back();
stack.pop_back();
Object * code2 = stack.back();
stack.pop_back();

if(pred->getType() != STRING || code->getType() != STRING || code2->getType() != STRING){
    cerr<<"Argument mismatch exception"<<endl;
    return;
}

    list<Object*> newStack;
    arb->executeString(((String*)pred)->getString(),newStack,context);

    if(!newStack.size())
        return;

    Object* t = newStack.back();

    if(obj2Bool(t))
        arb->executeString(((String*)code)->getString(),stack,context);
    else
        arb->executeString(((String*)code2)->getString(),stack,context);
}

void While::execute(list<Object*> &stack, map<string,Object*> &context){
if(stack.size()< 2){
cerr<<"not enough args!"<<endl;
return;
}
Object * pred = stack.back();
stack.pop_back();
Object * code = stack.back();
stack.pop_back();

if(pred->getType() != STRING || code->getType() != STRING){
    cerr<<"Argument mismatch exception"<<endl;
    return;
}

    for(;;){
        list<Object*> newStack;
        arb->executeString(((String*)pred)->getString(),newStack,context);

        if(!newStack.size())
            return;

        Object* t = newStack.back();

        if(!obj2Bool(t))
            return;

        arb->executeString(((String*)code)->getString(),stack,context);

        if(context.find("done") != context.end()){
            if(context["done"]->getType() == INT)//continue
                context.erase("done");
            else
                break;
        }
    }

    if(context.find("done") != context.end())
            if(context["done"]->getType() == FLOAT)//break
                context.erase("done");


}
