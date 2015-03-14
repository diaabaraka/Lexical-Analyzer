#ifndef STATE_H
#define STATE_H
#include <map>
#include<vector>
#include <set>
#include <string>
using namespace std;

class State
{
public:
    State();
    State(int state_ID);
    bool isAccepting();
//        vector<> getEdges();
    int get_Id();

    multimap<string , State*> getAllTransitions();
    void addTransition(string input,State* dest);
   void getTrasitions(string input,vector<State*>&destStates);
private:
    int state_Id;
//        vector<> Edges;
    multimap<string,State*>transitions;
    //Include all states that can be reached from this state with a specific input.
    set<State*>NFAstates;
    bool acceptingState;




};

#endif // STATE_H
