//#include <iostream>
//#include "NFA.h"
//#include <fstream>
//#include"DFA.h"
//#include "Tranzation.h"
//
//using namespace std;
//
//int main()
//{
//
//  string line;
//  ifstream myfile ("most.txt");
//  NFA* x = new NFA();
//
//  if (myfile.is_open())
//  {
//    while ( getline (myfile,line) )
//    {
//
//           x->parse(line);
//
//    }
//    myfile.close();
//  }
//
//    State* start = x->compine();
////            set<string>input_2 = x->getInputSet();
////
////        set<string, State*>::iterator iter;
////
////        for (iter = input_2.begin(); iter != input_2.end(); ++iter) {
////
////            cout<<*iter<<endl;
////
////        }
////    cout<<"parse finsh \n";
//    set<string>input = x->getInputSet();
//	DFA* dfa=new DFA(start,&input);
//  	dfa->convertToDFA();
//  	vector<State*>dfaTable=dfa->getDfaTable();
//
//
//
//
//   // x->BFS(dfaTable[0]);
////    cout<<"DFA finish\n";
//       set<string>keyWards= x->keyWords;
//   set<string>punc = x->punctuation;
//
// Tranzation* tranzation = new Tranzation (input , dfaTable,keyWards,punc );
//
//   tranzation->read();
//
//    return 0;
//}
