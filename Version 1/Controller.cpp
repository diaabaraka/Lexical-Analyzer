//#include <iostream>
//#include "NFA.h"
//#include <fstream>
//#include"DFA.h"
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
//    set<string>input = x->getInputSet();
//	DFA* dfa=new DFA(start,&input);
//  	dfa->convertToDFA();
//  	vector<State*>dfaTable=dfa->getDfaTable();
//    x->BFS(dfaTable[0]);
//
//    return 0;
//}
