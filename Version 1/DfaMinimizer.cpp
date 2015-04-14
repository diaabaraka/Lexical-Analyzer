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
#include <sstream>
#include <fstream>

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

vector <vector <State*> > finalTable;

vector <State*> finalMinimizedStates;


vector <State*> DfaMinimizer::getFinalMinimzedStates() {
 return finalMinimizedStates;
}



 int * DfaMinimizer::setTheMappingArr( vector <vector <State*> > working_set,int n){

  int *arr=new int [n];

  REP(i,SZ(working_set)){

 vector <State*> v=working_set[i];

  REP(j,SZ(v)){

  State* s= v[j];

   arr[s->get_Id()]=i;

  }

  }


   return arr;

   }


string DfaMinimizer::hashingFunction( vector <int> GoingToStatesVector)
{
  string str="";

  REP(i,SZ(GoingToStatesVector)){

  str+=GoingToStatesVector[i];

  }



 return str;
}








 void DfaMinimizer::minimize(vector <State*> allStates,set <string> inputSet){

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
   /////////////////////////////////////////////////////////////////////////////

   map <string , vector<State*> > hmap;

  vector <State*> vv=working_set[0];
    REP(i, SZ(vv)){

 State* s=vv[i];
 string hf=s->getType();

  if(hmap.count(hf)){

  hmap.find(hf)->second.pb(s);

  }
else{
vector <State*> v;
v.pb(s);
  hmap[hf]=v;

}

  }

   vector <vector <State* > > last;
   last.pb(working_set[1]);
 map<string, vector<State*> >::iterator it;

   for (it = hmap.begin(); it != hmap.end(); it++)
{

 last.pb(it->second);

}

   CreateTheTwoDArray(last,SZ(allStates),inputSet,allStates);

return;

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

State* DfaMinimizer::getState(int goingtoID,vector <State*>allStates){

 REP(i,SZ(allStates)){

 if(allStates[i]->get_Id()==goingtoID){
    return allStates[i];
 }

 }

 return NULL;

}


  void DfaMinimizer::  drawTable(vector <State*> allNewStates, set <string> inputSet){


  finalMinimizedStates=allNewStates;

    ofstream myfile;
  myfile.open ("Drawing.txt");

  //  myfile << "Writing this to a file.\n";
  myfile<<endl;

    map<string , int> ID;
    set<string>::iterator iter;

   myfile<<"     ";
   int x = 0;

     for (iter = inputSet.begin(); iter != inputSet.end(); ++iter)
        {
        string input=*iter;
        myfile<<input<<" ";

          }

     myfile<<endl;

  REP(i,SZ(allNewStates)){

    State* s=allNewStates[i];

   myfile<<s->get_Id()<<" $  ";

 for (iter = inputSet.begin(); iter != inputSet.end(); ++iter)
        {
        string input=*iter;
      vector <State*> v;
      v.clear();

   //   myfile<<input<<endl;

   s->getTrasitions(input,v);

   if(SZ(v)>0){
    myfile<<v[0]->get_Id()<<" ";
   }
   else{
    myfile << "  ";
   }
    }
 myfile <<endl;

  }


 myfile.close();

    }






void  DfaMinimizer::sendToNextStage(vector <vector <State*> > working_set,int n,set <string> inputSet,vector<State*> allStates){


  REP(i,SZ(working_set)){
    vector<State*> temp = working_set[i];
    finalTable.pb(temp);
  }


//   REP(i,SZ(finalTable)){
//      vector<State*> temp = finalTable[i];
//   REP(j,SZ(temp)){
//       cout<<temp[j]->get_Id()<<" "<<endl;
//   }
//   cout<<endl;
//  }
// cout<<endl;

   int * mappingArr=setTheMappingArr(finalTable,n);


     set<string>::iterator iter;


//     for (iter = inputSet.begin(); iter != inputSet.end(); ++iter)
//        {
//        string input=*iter;
//        cout<<input<<" ";
//          }


  vector <State*> allNewStates;

  vector <State*> allStatesNew;

  // cout<<SZ(finalTable)<<"aho"<<endl;
//
   REP(i,SZ(finalTable)){

      State *s=new State(i);


      allStatesNew.pb(s);
   }
//
//
//
//

   REP(i,SZ(finalTable)){

     State* s=getState(i,allStatesNew);

      vector<State*> v=finalTable[i];
      State* old=v[0];

  bool f=false;

  //  if(old->getType().compare("assign")==0){cout<<"leeeeeeeeeeeeeeeeeeeeeeeeeh"<<endl; f=true;}


      if(old->isAccepting()){
        s->setAccepting();
      }


    s->set_Type(old->getType());


        vector <State*> tempGoingToVector;
     vector <int> GoingToStatesVector;
         GoingToStatesVector.clear();

       set<string>::iterator iter;


     for (iter = inputSet.begin(); iter != inputSet.end(); ++iter)
        {

        string input=*iter;
          tempGoingToVector.clear();

     old->getTrasitions(input, tempGoingToVector);


            if(SZ(tempGoingToVector)>0){

     State* goingToState=tempGoingToVector[0];


        int goingtoID=mappingArr[goingToState->get_Id()];


          State* going=getState(goingtoID,allStatesNew); // allStates newwwwwwwww

          s->addTransition(input,going);


            }

        }


  // if(f)
 //  cout<<"new leeeeeeeeeeeeeeeeeeeeeeh   " <<s->get_Id()<<endl;



  allNewStates.pb(s);

      }



   // send allnewStates

  drawTable(allNewStates,inputSet);


  return;



}

 bool DfaMinimizer::equals(vector <vector <State*> > working_set,vector <vector <State*> > working_set2){

  if(SZ(working_set)!=SZ(working_set2))return false;

   REP(i,SZ(working_set)){

   vector <State*> v1=working_set[i];
   vector <State*> v2=working_set2[i];

   if(SZ(v1)!=SZ(v2))return false;

   REP(j,SZ(v1))  {

   if(v1[j]->get_Id()!=v2[j]->get_Id())return false;

   }



   }
return true;

 }




  void DfaMinimizer::CreateTheTwoDArray(vector <vector <State*> > working_set,int n,set <string> inputSet,vector<State*>allStates){


   while(1){

   map <string , vector<State*> > hmap;

    int * mappingArr=setTheMappingArr(working_set,1000); ///////////


   REP(i,SZ(working_set)){

   vector <State*> working_vector=working_set[i];

  string constt="b";

 int a = i;
stringstream ss;
ss << a;
string str = ss.str();

   constt.append(str);

     REP(j,SZ(working_vector)){     // hena 3la mostawa el magmo3a el wa7da

  //hmap.clear();

   if(SZ(working_vector)==1) {

    finalTable.pb(working_vector);

        break;  ////////////////////////
   }

   State* s= working_vector[j];

  vector <State*> tempGoingToVector;

      tempGoingToVector.clear();
     vector <int> GoingToStatesVector;
         GoingToStatesVector.clear();

    set<string>::iterator iter;



        for (iter = inputSet.begin(); iter != inputSet.end(); ++iter)
        {

        string input=*iter;

     s->getTrasitions(input, tempGoingToVector);

            if(SZ(tempGoingToVector)>0){

     State* goingToState=tempGoingToVector[0];

          GoingToStatesVector.pb(mappingArr[goingToState->get_Id()]);
            }

        }


   // state S going to GoingtoStatesVector states

  string hf=constt+hashingFunction(GoingToStatesVector);

  //  hf+=s->getType();


  if(hmap.count(hf)){

  hmap.find(hf)->second.pb(s);

  }
else{
vector <State*> v;
v.pb(s);

 //cout<<hf<<endl;

  hmap[hf]=v;

}


    }




   }


vector <vector <State*> > working_set2;

 working_set2=makeTheNewWorkSet(hmap);


 if( equals(working_set,working_set2) ){

    sendToNextStage(working_set,n,inputSet,allStates);

  return;

 }

 working_set=working_set2;



   }

 return;

  }



DfaMinimizer::DfaMinimizer(vector <State*> allStates,set<string> inputSet)
{

    minimize(allStates,inputSet);


}





DfaMinimizer::~DfaMinimizer()
{
    //dtor
}
