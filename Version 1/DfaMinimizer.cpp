#include "DfaMinimizer.h"
#include "DFA.h"
#include "State.h"
#include <map>
#include <iostream>
#include <cmath>
#include <typeinfo>
#include <string>
#include <stack>
#include <map>
#include <deque>
#include <vector>
#include <set>
#include <algorithm>
#include <list>

#include <set>
#include <string>

#define pb push_back
#define se second

#define all(c) (c).begin(), (c).end()
#define SORT(c) sort(all(c))

#define C(a) memset((a),0,sizeof(a))

#define VI vector <int>
#define ll long long

#define SZ(V) (int)V.size()

#define FOR(i, a, b) for(int i = (a); i < (b); ++i)
#define RFOR(i, b, a) for(int i = (b) - 1; i >= (a); --i)
#define REP(i, N) FOR(i, 0, N)
#define RREP(i, N) RFOR(i, N, 0)
#define FILL(A,value) memset(A,value,sizeof(A))




 int * DfaMinimizer::setTheMappingArr( vector <vector <State*> > working_set,int n){

  int arr[n];

  REP(i,SZ(working_set)){

  REP(j,SZ(working_set[i])){

  State* s= working_set[i][j];

   arr[s->get_Id()]=i;

  }

  }

   }


string DfaMinimizer::hashingFunction( vector <State*> GoingToStatesVector)
{
  string str="";

  REP(i,SZ(GoingToStatesVector)){

  str+=GoingToStatesVector[i]->get_Id();

  }


}








 void DfaMinimizer::minimize(vector <State*> allStates){

 vector <vector <State*> > working_set;

  vector <State*> acceptingStates;
  vector <State*>  regularStates;

  working_set.pb(acceptingStates);
  working_set.pb(regularStates);

  REP(i,SZ(allStates)){

  State* s= allStates[i];

   if(s->isAccepting()){
    working_set[0].pb(s);
   }
   else{
    working_set[1].pb(s);
   }
  }
//***********************

    int * mappingArr=setTheMappingArr(working_set,SZ(allStates));



   CreateTheTwoDArray(working_set,SZ(allStates),mappingArr);



}


vector <vector <State*> > DfaMinimizer::makeTheNewWorkSet( map <string , vector<State*> > hmap ){

 vector <vector <State*> > working_set;

map<string, vector<State*> >::iterator it;

for (it = hmap.begin(); it != hmap.end(); it++)
{

 working_set.pb(it->second);

}

 return working_set;
}

void  DfaMinimizer::sendToNextStage(vector <vector <State*> > working_set){



}

  void DfaMinimizer::CreateTheTwoDArray(vector <vector <State*> > working_set,int n,int * mappingArr){


   while(1){

   map <string , vector<State*> > hmap;

   REP(i,SZ(working_set)){

   vector <State*> working_vector=working_set[i];

    REP(j,SZ(working_vector)){

   State* s= working_vector[j];

  vector <State*> tempGoingToVector;
      tempGoingToVector.clear();
     vector <State*> GoingToStatesVector;
         GoingToStatesVector.clear();

    set<string>::iterator iter;

         set<string>inputSet;            ////////////// waiting for consturctor

        for (iter = inputSet.begin(); iter != inputSet.end(); ++iter)
        {
        string input=*iter;

     s->getTrasitions(input, tempGoingToVector);

     State* goingToState=tempGoingToVector[0];

       GoingToStatesVector.pb(goingToState);

        }
   // state S going to GoingtoStatesVector states

   string hf=hashingFunction(GoingToStatesVector);

  if(hmap.count(hf)){

  hmap.find(hf)->second.pb(s);

  }
else{
vector <State*> v;
v.pb(s);
hmap[hf]=v;
}




    }



   }

vector <vector <State*> > working_set2;

 working_set2=makeTheNewWorkSet(hmap);
 // compare

 if( equal(working_set.begin(), working_set.end(), working_set2.begin()) ){

    sendToNextStage(working_set);

 }

 working_set=working_set2;

   }


  }



DfaMinimizer::DfaMinimizer(vector <State*> allStates)
{
    minimize(allStates);
}





DfaMinimizer::~DfaMinimizer()
{
    //dtor
}
