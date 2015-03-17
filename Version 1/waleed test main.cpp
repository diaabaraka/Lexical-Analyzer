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
State* stb=new State(1);
State* sth=new State(7);
 State* sta=new State(0);
 State* stc=new State(2);
 State* stdd=new State(3);
 State* ste=new State(4);
 State* stf=new State(5);
 State* stg=new State(6);
State* sti=new State(8);



  sta->addTransition("1",stb);
  sta->addTransition("2",stc);
sta->addTransition("3",stdd);


  stb->addTransition("1",ste);
  stb->addTransition("2",ste);
 stb->addTransition("3",ste);


  stc->addTransition("1",ste);
  stc->addTransition("2",ste);
 stc->addTransition("3",ste);

  stdd->addTransition("1",ste);
  stdd->addTransition("2",ste);
  stdd->addTransition("3",ste);

   ste->addTransition("1",stf);
  ste->addTransition("2",stg);
   ste->addTransition("3",sth);

   stf->addTransition("1",sti);
  stf->addTransition("2",sti); //
   stf->addTransition("3",sti);

   stg->addTransition("1",sti);
  stg->addTransition("2",sti);
   stg->addTransition("3",sti);

   sth->addTransition("1",sti);
 // sth->addTransition("0",st6);
  // sth->addTransition("1",st5);


 sti->setAccepting();

 vector <State*> v;
  v.push_back(sta);
  v.push_back(stb);
  v.push_back(stc);
  v.push_back(stdd);
  v.push_back(ste);
  v.push_back(stf);
  v.push_back(stg);
  v.push_back(sth);
v.push_back(sti);


  DfaMinimizer* df=new DfaMinimizer(v);

  return 0;
}
