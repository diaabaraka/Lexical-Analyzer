#include "DfaMinimizer.h"
#include "DFA.h"
#include "State.h"
#include <map>

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

     vector< vector<int> > myVector;

   CreateTheTwoDArray(working_set,SZ(allStates),mappingArr);

   // loop on work_set
   // categorize every state at the specific vector now in the 2D vector< vector<int> > myVector;
   // make the new working set
   // back to loop :D

}

  void DfaMinimizer::CreateTheTwoDArray(vector <vector <State*> > working_set,int n,int * mappingArr){

 vector<vector<double> > array2D;

  array2D.resize(n);
  for (int i = 0; i < n; ++i)
    array2D[i].resize(n);

  // Put some values in
 // array2D[1][2] = 6.0;
  // array2D[3][1] = 5.5;


   REP(i,SZ(working_set)){

   vector <State*> working_vector=working_set[i];

    REP(j,SZ(working_vector)){

   State* s= working_vector[j];

     vector <State*> goingToVector;

     //   waiting for input

     string input="a";

     s->getTrasitions(input, goingToVector);

     State* goingToState=goingToVector[0];


    }


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
