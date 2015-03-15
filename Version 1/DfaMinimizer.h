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
         int * setTheMappingArr( vector <vector <State*> > working_set,int n);
        virtual ~DfaMinimizer();
    protected:
    private:
};

#endif // DFAMINIMIZER_H
