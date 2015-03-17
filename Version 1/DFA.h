#ifndef DFA_H
#define DFA_H
#include <map>

#include <set>
#include <string>
#include"State.h"

#include <string>
#include <stack>
#include <map>
#include <deque>
#include <vector>
#include <set>
#include <algorithm>
#include <list>

using namespace std;
class DFA
{
public:
    DFA(State*start,set<string>*input);
    virtual ~DFA();
    void epsilonClosure(set<State*>states,set<State*>&result);
    void moveTransition(set<State*>states,string input,set<State*>&result);
    void convertToDFA(void);
    vector<State*> getDfaTable();
    void printState(set<State*>*Set);

protected:
private:
    vector<State*>DFAtable;
    State*startingState;
    set<string>inputSet;
};

#endif // DFA_H
