#include "State.h"
#include <map>

#include <set>
#include <string>
using namespace std;
State::State()
{
    //ctor
    acceptingState = false;
}

State::State(int state_ID)
{

    state_Id = state_ID;
    acceptingState = false;


}
//This constructor is only for DFA states.
State::State(int state_ID,set<State*>&nfaStates)
{
    state_Id=state_ID;
    NFAstates=nfaStates;
    // Now we should check if this state is accepting state or not.
    acceptingState=false;//Intially
    set<State*>::iterator iter;
    State*st;
    for (iter = NFAstates.begin(); iter != NFAstates.end(); ++iter)
    {
        st=*iter;
        if(st->isAccepting())
        {
            acceptingState=true;//for the new DFA state
            set_Type(st->getType());
            break;
        }
    }
}
bool State :: isAccepting()
{

    return acceptingState;


}
//State :: vector<> getEdges(){
//
//    return Edges;
//
//
//}
int State :: get_Id()
{

    return state_Id;



}

void State :: setAccepting(){

    acceptingState = true;
 //   cout<<"this is the time number  "<<state_Id<<endl;
   // h++;

}

void State:: addTransition(string input,State* dest)
{

    transitions.insert(make_pair(input,dest));


}
void State:: getTrasitions(string input,vector<State*>&destStates)
{
    destStates.clear();
    multimap<string, State*>::iterator st;

    for(st = transitions.lower_bound(input); st != transitions.upper_bound(input); ++st)
       destStates.push_back(st->second);
}

multimap<string, State*> State:: getAllTransitions(){

    return transitions;


}
void State::getNFAstates(set<State*>&nfaSstates){
    nfaSstates=NFAstates;


}

string State :: getType()
    {
    return classType ;

    }

 void State :: set_Type (string type )
    {

    classType = type ;

    }


