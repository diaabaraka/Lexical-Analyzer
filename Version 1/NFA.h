
#ifndef NFA_H
#define NFA_H

#include "State.h"
#include <string>
#include <map>
#include <stack>
using namespace std;

class NFA
{
    public:
        NFA();
        void parse(string expression);
        State compine();
        string postfix(string expression);
        bool high_priority(char first , char top);



    protected:
    private:
        map<string , State>regular_expression;
        map<string , State>regular_definition;
        int counter = 0;


};

#endif // NFA_H
