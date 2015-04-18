#include <iostream>
#include "NFA.h"
#include <fstream>
#include"DFA.h"
#include "Follow.h"
#include "First.h"
#include "ParsingTable.h"
#include "StartToParser.h"
#include "Tranzation.h"

#include "DfaMinimizer.h"
#include "ParsingTable.h"
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

   // object tranzation for diaa to use getNextToken() method

  /////////////////////////////////////////////////////////////////////////


  multimap<string,string> rules;



  multimap<string,string> follow_map;


map <string,map <string,string> > finalTable;

  string myints[] = {"id","+","-","(",")","$"};

  set<string> allNonTerminals (myints,myints+6);



//
follow_map.insert(make_pair("E","$"));
follow_map.insert(make_pair("E",")"));
follow_map.insert(make_pair("E'","$"));
follow_map.insert(make_pair("E'",")"));
follow_map.insert(make_pair("T","+"));
follow_map.insert(make_pair("T",")"));
follow_map.insert(make_pair("T","$"));
follow_map.insert(make_pair("T'","+"));
follow_map.insert(make_pair("T'",")"));
follow_map.insert(make_pair("T'","$"));

follow_map.insert(make_pair("F","+"));
follow_map.insert(make_pair("F",")"));
follow_map.insert(make_pair("F","$"));
follow_map.insert(make_pair("F","*"));


  StartToParser *startToParser =new StartToParser();

//   string startSymbol =startToParser.startingSymbol ;  // diaa needs it

   set<string>Terminals = startToParser->terminals; // diaa , waleed  , mostafa and mahmoud need it

   // startToParser->fillGrammerList();   //to fill the multimap

  /////////////////////////////////////////////////////////////////////

 First *firstobj=new First();
  multimap <string,string > first_map=firstobj->getAllFirst();

  startToParser->fillGrammerList();

rules=startToParser->grammers;




cout<<"7amoo"<<endl;

  //Follow *f=new Follow();

 // multimap  <string,string> follow_map = f->getAllFollow();

  cout<<"ahoooooooooooo"<<endl;

   ParsingTable* pt=new ParsingTable(rules,first_map,follow_map,allNonTerminals);  // parsing table waleeeeed

  map<string,map<string,string> > fkk= pt->getFinalTable() ; // from waleed to diaa 7awell from waleed to diaa 7awell hal tasm3ony ?


//  map <string,map <string,string> >::iterator its;
//
//
//  for (its=fkk.begin(); its!=fkk.end();its=fkk.upper_bound(its->first)){
//
//  cout<<its->first<<"   " ;
//
// map<string,string>mmm= its->second;
//
//   for (set<string>::iterator it=allNonTerminals.begin(); it!=allNonTerminals.end(); ++it){
//
//
//            if(mmm.count(*it)){
//             cout<<*it<<":"<<mmm.find(*it)->second<<"      ";
//            }
//
//
//  }
//  cout<<endl;
//  cout<<"______________________________________________________________________";
//  cout<<endl;
//  cout<<endl;
//  }



    return 0;
}
