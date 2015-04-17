#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <deque>
#include <algorithm>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <iostream>
using namespace std;
class Parser
{
public:
    Parser( string start,vector<string>*in,set<string>*t,map<string, map<string,string> >*table);
    virtual ~Parser();
    void genParseTree();
protected:
private:
    string start_symbol;
    vector<string>inputs;

    /*
    each key is a non-terminal symbol and its value is another map.
    For the second map, each key is a terminal symbol or the special symbol $
    and each entry holds a production rule.
    */
    map<string, map<string,string> > parsing_table;
    set<string>terminals;

};


#endif // PARSER_H
