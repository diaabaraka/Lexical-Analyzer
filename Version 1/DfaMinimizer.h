#ifndef DFAMINIMIZER_H
#define DFAMINIMIZER_H
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

class DfaMinimizer
{
    public:
          void  drawTable(vector <State*> allNewStates, set <string> inputSet);

        DfaMinimizer(vector <State*> allStates,set <string>inputSet);

        void minimize(vector <State*> allStates,set <string> inputSet);

    bool equals(vector <vector <State*> > working_set,vector <vector <State*> > working_set2);
        string hashingFunction( vector <int> GoingToStatesVector);

        vector <vector <State*> > makeTheNewWorkSet( map <string , vector<State*> > hmap );
      void sendToNextStage(vector <vector <State*> > working_set,int n,set <string> inputSet,vector<State*> allStates);
      State* getState(int goingtoID,vector <State*>allStates);

         int * setTheMappingArr( vector <vector <State*> > working_set,int n);
 void CreateTheTwoDArray(vector <vector <State*> > working_set,int n,set <string> inputSet,vector<State*> allStates);
        virtual ~DfaMinimizer();
    protected:
    private:
};

#endif // DFAMINIMIZER_H
