#include "State.h"
#include <map>

#include <set>
#include <string>
using namespace std;
State::State()
{
    //ctor
}

State::State(int state_ID)
{

    state_Id = state_ID;

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

string State :: getType()
    {
    return classType ;

    }

 void State :: set_Type (string type )
    {

    classType = type ;

    }


