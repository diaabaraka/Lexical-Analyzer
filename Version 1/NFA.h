
#ifndef NFA_H
#define NFA_H

#include "State.h"
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <string.h>
#include <stack>
using namespace std;

class NFA
{
    public:
        NFA();
        string parse(string expression);
        State* compine();
        string postfix(string expression);
        bool high_priority(char first , char top);
        bool isOperator(char x);
        bool isChar(char x);
        string addConcatenation(string expr);
        void checkOperator(string expr, bool dete[] );
        State* Eval(string postFix);
        void BFS(State* x);
        string AddEscape(string x);
        pair<State* , State*> cloneGraph(State* x);
        set<string> getInputSet();
        set<string> keyWords;
        set<string> punctuation;
    protected:
    private:
        map<string , State*>regular_expression;
        map<string , State*>regular_definition;
        set<string> inputSet;
        queue<char> special;
        int counter = 0;
        State* startState ;
        string exprName;
        bool regularDefinition;



};

#endif // NFA_H
