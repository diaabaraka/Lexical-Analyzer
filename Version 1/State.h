#ifndef STATE_H
#define STATE_H


class State
{
    public:
        State();
        State(int state_ID);
        bool isAccepting();
//        vector<> getEdges();
        int get_Id();


    private:
        int state_Id;
//        vector<> Edges;
        bool acceptingState;




};

#endif // STATE_H
