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
        DfaMinimizer(vector <State*> allStates);
        void minimize(vector <State*> allStates);
        string hashingFunction( vector <State*> GoingToStatesVector);

        vector <vector <State*> > makeTheNewWorkSet( map <string , vector<State*> > hmap );
      void sendToNextStage(vector <vector <State*> > working_set);

         int * setTheMappingArr( vector <vector <State*> > working_set,int n);
 void CreateTheTwoDArray(vector <vector <State*> > working_set,int n,int * mappingArr);
        virtual ~DfaMinimizer();
    protected:
    private:
};

#endif // DFAMINIMIZER_H
