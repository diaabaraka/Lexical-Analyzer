#ifndef STATE_H
#define STATE_H
#include <map>
#include<vector>
#include <set>
#include <string>
#include <iostream>
using namespace std;

class State
{
public:
    State();
    State(int state_ID);
    State(int stat_ID,set<State*>&nfaStates);
    bool isAccepting();
    void setAccepting();
//        vector<> getEdges();
    int get_Id();

    multimap<string , State*> getAllTransitions();
    void addTransition(string input,State* dest);
   void getTrasitions(string input,vector<State*>&destStates);
   void set_Type (string type ) ;
    void getNFAstates(set<State*>&nfaSstates);
    string getType() ;


private:
    int state_Id;
//        vector<> Edges;
    multimap<string,State*>transitions;
    //Include all states that can be reached from this state with a specific input.
    set<State*>NFAstates;
    bool acceptingState;
    string classType ;
    //int h = 0;




};

#endif // STATE_H
