#include "DfaMinimizer.h"

DfaMinimizer::DfaMinimizer(vector <State*> allStates)
{
    minimize(allStates);
}


DfaMinimizer::minimize(vector <State*> allStates){

 vector <vector <State*> > working_set;

  vector <State*> acceptingStates;
  vector <State*>  regularStates;

  working_set.pb(acceptingStates);
  working_set.pb(regularStates);

  REP(i,SZ(allStates)){

  State* s= allStates[i];

   if(s.isAccepting()){
    working_set[0].pb(s);
   }
   else{
    working_set[1].pb(s);
   }
  }
//***********************

    int mappingArr[]=setTheMappingArr(working_set,SZ(allStates));

   // loop on work_set
   // categorize every state at the specific vector now in the 2D vector< vector<int> > myVector;
   // make the new working set
   // back to loop :D

}



DfaMinimizer::int [] setTheMappingArr(working_set,int n){

  int arr[n];

  REP(i,SZ(working_set)){

  REP(j,SZ(working_set[i])){

  State* s= working_set[i][j];

   arr[s.get_Id()]=i;

  }

  }

   }



DfaMinimizer::~DfaMinimizer()
{
    //dtor
}
