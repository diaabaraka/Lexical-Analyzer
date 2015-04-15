#ifndef STARTTOPARSER_H
#define STARTTOPARSER_H
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
class StartToParser
{
    public:
        StartToParser();
        virtual ~StartToParser();

        string startingSymbol = "METHOD_BODY" ;

        std::set<std::string> terminals ;

        multimap <string, string> grammers ;




        void fillGrammerList();

    protected:
    private:
};

#endif // STARTTOPARSER_H
