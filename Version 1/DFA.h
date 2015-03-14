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
    DFA();
    virtual ~DFA();
    void epsilonClosure(set<State*>states,set<State*>&result);
    void moveTransition(set<State*>states,string input,set<State*>&result);
protected:
private:
};

#endif // DFA_H
