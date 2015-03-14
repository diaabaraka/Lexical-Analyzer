#include "State.h"

State::State()
{
    //ctor
}

State::State(int state_ID){

    state_Id = state_ID;

}
bool State :: isAccepting(){

    return acceptingState;


}
//State :: vector<> getEdges(){
//
//    return Edges;
//
//
//}
int State :: get_Id(){

    return state_Id;



}
