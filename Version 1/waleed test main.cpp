//// constructing multimaps
//#include <iostream>
//#include <map>
//#include "State.h"
//#include "DfaMinimizer.h"
//
//bool fncomp (char lhs, char rhs) {return lhs<rhs;}
//
//struct classcomp {
//  bool operator() (const char& lhs, const char& rhs) const
//  {return lhs<rhs;}
//};
//
//int main ()
//{
//
//
//State* st1=new State(1);
//State* st7=new State(7);
// State* st8=new State(8);
// State* st2=new State(2);
// State* st3=new State(3);
// State* st4=new State(4);
// State* st5=new State(5);
// State* st6=new State(6);
//
//
//
//  st8->addTransition("a",st7);
//  st8->addTransition("b",st3);
//
//
//  st1->addTransition("a",st2);
//  st1->addTransition("b",st6);
//
//
//  st7->addTransition("a",st7);
//  st7->addTransition("b",st5);
//
//  st2->addTransition("a",st7);
//  st2->addTransition("b",st3);
//
//   st3->addTransition("a",st1);
//  st3->addTransition("b",st3);
//
//   st4->addTransition("a",st3);
//  st4->addTransition("b",st7); //
//
//   st5->addTransition("a",st8);
//  st5->addTransition("b",st6);
//
//   st6->addTransition("a",st3);
//  st6->addTransition("b",st7);
//
// st3->setAccepting();
//
// vector <State*> v;
//  v.push_back(st8);
//  v.push_back(st1);
//  v.push_back(st2);
//  v.push_back(st7);
//  v.push_back(st3);
//  v.push_back(st4);
//  v.push_back(st5);
//  v.push_back(st6);
//
//
//  DfaMinimizer* df=new DfaMinimizer(v);
//
//  return 0;
//}
