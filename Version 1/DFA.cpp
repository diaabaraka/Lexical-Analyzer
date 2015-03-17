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
DFA::DFA(State*start,set<string>*input)
{
    startingState=start;
    inputSet=*input;
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

        curr->getTrasitions("-1",destStates);
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
void DFA  ::convertToDFA()
{
    int ID_counter=0;
    DFAtable.clear();
    set<State*>NFAstartingStates;
    NFAstartingStates.insert(startingState);//here we have starting states of NFA

    set <State*>epsilonStates;



    epsilonClosure(NFAstartingStates,epsilonStates);

    // now DFAstartinng states include all states that reached from the
    //NFAstarting states by epsilon input.
    State *DFAstartingState=new State(ID_counter++,epsilonStates);
//    set<State*>x;
//    DFAstartingState->getNFAstates(x);

    DFAtable.push_back(DFAstartingState);
    vector <State*> unmarkedStates;
    unmarkedStates.push_back(DFAstartingState);
    State*curr;
    set<State*>NFAstates;
    set<State*>moveStates,epsilonOfMoves,token;
    string input;
    while(!unmarkedStates.empty())
    {
        curr=unmarkedStates[unmarkedStates.size()-1];
        unmarkedStates.pop_back();
        curr->getNFAstates(NFAstates);


        set<string>::iterator iter;
        for (iter = inputSet.begin(); iter != inputSet.end(); ++iter)
        {
            input=*iter;
            moveTransition(NFAstates,input,moveStates);


            epsilonClosure(moveStates,epsilonOfMoves);


            State *st;
            int i=0;
            for(; i<DFAtable.size(); i++)
            {
                st=DFAtable[i];
                st->getNFAstates(token);
                if(token==epsilonOfMoves)
                {
                    curr->addTransition(input,st);
                    break;
                }


            }
            if(i==DFAtable.size()&&epsilonOfMoves.size()!=0)
            {
//                                printState(&epsilonOfMoves);
//                cout<<"\n------------------\n";
//cout<<ID_counter;
                State* newState=new State(ID_counter++,epsilonOfMoves);
                DFAtable.push_back(newState);
                unmarkedStates.push_back(newState);
                curr->addTransition(input,newState);
            }


        }


    }






}
vector<State*> DFA:: getDfaTable()
{

    return DFAtable;


}

void DFA::printState(set<State*>*Set)
{
    set<State*>s=*Set;State* st;
    set<State*>::iterator iter;

    for (iter = s.begin(); iter != s.end(); ++iter)
    {
        st=*iter;
        cout<<st->get_Id()<<" : "<<endl;



    }
}

DFA::~DFA()
{
    //dtor
}
