#include <iostream>
#include "NFA.h"
#include <fstream>
#include"DFA.h"
#include "Tranzation.h"
#include "DfaMinimizer.h"

#define SZ(V) (int)V.size()



using namespace std;

int main()
{

  string line;
  ifstream myfile ("most.txt");
  NFA* x = new NFA();

  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {

           x->parse(line);

    }
    myfile.close();
  }

    State* start = x->compine();

    set<string>input = x->getInputSet();
	DFA* dfa=new DFA(start,&input);
  	dfa->convertToDFA();
  	vector<State*>dfaTable=dfa->getDfaTable();

    x->BFS(dfaTable[0]);
 DfaMinimizer* dm=new DfaMinimizer(dfaTable,input);

  vector <State*> vvvv=dm->getFinalMinimzedStates();

    State* ss;
    int i=0;
     for(i;i<SZ(vvvv);i++){
      if(vvvv[i]->get_Id()==1){
        ss=vvvv[i];
      }
     }

     vvvv.erase (vvvv.begin()+1);

     vector <State*> finnnnn;
     finnnnn.push_back(ss);
   i=0;
  for(i;i<SZ(vvvv);i++){
    finnnnn.push_back(vvvv[i]);
  }


   // x->BFS(dfaTable[0]);
//    cout<<"DFA finish\n";
       set<string>keyWards= x->keyWords;
   set<string>punc = x->punctuation;

 Tranzation* tranzation = new Tranzation (input , finnnnn ,keyWards,punc );

   tranzation->read();

    return 0;
}
