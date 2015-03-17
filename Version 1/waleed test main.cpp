// constructing multimaps
#include <iostream>
#include <map>
#include "State.h"
#include "DfaMinimizer.h"

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

int main ()
{
State* st1=new State(1);
State* st7=new State(7);
 State* st0=new State(0);
 State* st2=new State(2);
 State* st3=new State(3);
 State* st4=new State(4);
 State* st5=new State(5);
 State* st6=new State(6);



  st0->addTransition("1",st1);
  st0->addTransition("0",st7);


  st1->addTransition("1",st0);
  st1->addTransition("0",st7);


  st7->addTransition("1",st2);
  st7->addTransition("0",st2);

  st2->addTransition("1",st5);
  st2->addTransition("0",st4);

   st3->addTransition("1",st5);
  st3->addTransition("0",st4);

   st4->addTransition("1",st6);
  st4->addTransition("0",st6); //

   st5->addTransition("1",st5);
  st5->addTransition("0",st5);

   st6->addTransition("1",st5);
  st6->addTransition("0",st6);

 st5->setAccepting();

 st6->setAccepting();

 vector <State*> v;
  v.push_back(st0);
  v.push_back(st1);
  v.push_back(st2);
  v.push_back(st7);
  v.push_back(st3);
  v.push_back(st4);
  v.push_back(st5);
  v.push_back(st6);


  DfaMinimizer* df=new DfaMinimizer(v);

  return 0;
}
