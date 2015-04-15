#ifndef PARSINGTABLE_H
#define PARSINGTABLE_H
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

using namespace std;

class ParsingTable
{
    public:
        map <string,map <string,string> > finalTable;
         map<string,map<string,string> > getFinalTable();
        ParsingTable(multimap<string,string> rules,multimap<string,string> first_map ,multimap<string,string> follow_map,  set<string> allNonTerminals);
       void findSync(multimap<string,string> follow_map,set <string> allTerminals,bool error);

        virtual ~ParsingTable();
    protected:
    private:
};

#endif // PARSINGTABLE_H
