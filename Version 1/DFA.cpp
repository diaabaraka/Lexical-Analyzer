#include "DFA.h"
#include "State.h"
#include <map>

#include <string>
#include <stack>
#include <map>
#include <deque>
#include <vector>
#include <set>
#include <algorithm>
#include <list>

#include <set>
#include <string>
DFA::DFA()
{
    //ctor
}
void DFA::epsilonClosure(set<State*>states,set<State*>&result)
{
    result.clear();
    result=states;//intialize the result with the orginal states.
    stack<State*>st;//to process on all states.

    set<State*>::iterator iter;
    for (iter = states.begin(); iter != states.end(); ++iter)
    {
        st.push(*iter);
    }
    State *curr;
    while(!st.empty())
    {
        curr=st.top();
        st.pop();

        vector<State*>destStates;
        //Assume that the input is epsilon=zero.

        curr->getTrasitions(0,destStates);
        State* s;
        for(int i=0; i<destStates.size(); i++)
        {
            s=destStates[i];
            if(result.find(s)==result.end())
            {
                result.insert(s);
                st.push(s);
            }
        }


    }




}
void DFA::moveTransition(set<State*>states,string input,set<State*>&result)
{
    result.clear();
    vector<State*>destStates;
    set<State*>::iterator iter;
    for (iter = states.begin(); iter != states.end(); ++iter)
    {
        State *curr=*iter;
        curr->getTrasitions(input,destStates);

        for(int i=0; i<destStates.size(); i++)
        {

            result.insert(destStates[i]);


        }

    }



}

DFA::~DFA()
{
    //dtor
}
