#include "StartToParser.h"
//#include "Controller.h"
#include <map>
#include <iostream>
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




string startingSymbol = "METHOD_BODY" ;

//std::string tmp[] = {"id", ";","int" , "float","if", "(", ")", "{" , "}" , "else", "while" , "=" , "relop" , "addop" , "mulop" , "num" , "+" , "-" };
//std::set<std::string> terminals(tmp, tmp + sizeof(tmp) / sizeof(tmp[0]));


multimap <string, string> grammers ;

void StartToParser::fillGrammerList()
{
    //cout<<terminals.size()<<"\n";



    grammers.insert(make_pair("E","T E'"));
    grammers.insert(make_pair("E'","+ T E'"));
    grammers.insert(make_pair("E'","e"));
    grammers.insert(make_pair("T","F T'"));
    grammers.insert(make_pair("T'","- F T'"));
    grammers.insert(make_pair("T'","e"));
    grammers.insert(make_pair("F","( E )"));
    grammers.insert(make_pair("F","id"));



//       grammers.insert(make_pair("METHOD_BODY","STATEMENT_LIST"));
//
//       grammers.insert(make_pair("STATEMENT_LIST","STATEMENT STATEMENT_LIST_2" ));
//
//       grammers.insert(make_pair("STATEMENT_LIST_2","STATEMENT STATEMENT_LIST_2"));
//
//       grammers.insert(make_pair("STATEMENT_LIST_2","e"));
//
//       grammers.insert(make_pair("STATEMENT","DECLARATION"));
//
//       grammers.insert(make_pair("STATEMENT","IF"));
//
//       grammers.insert(make_pair("STATEMENT","WHILE"));
//
//       grammers.insert(make_pair("STATEMENT","ASSIGNMENT"));
//
//       grammers.insert(make_pair("DECLARATION","PRIMITIVE_TYPE id ;"));
//
//
//
//       grammers.insert(make_pair("PRIMITIVE_TYPE","int"));
//
//       grammers.insert(make_pair("PRIMITIVE_TYPE","float"));
//
//       grammers.insert(make_pair("IF","if ( EXPRESSION ) { STATEMENT } else { STATEMENT }"));
//
//       grammers.insert(make_pair("WHILE" , "while ( EXPRESSION ) { STATEMENT }"));
//
//       grammers.insert(make_pair("ASSIGNMENT", "id = EXPRESSION ;" ));
//
//       grammers.insert(make_pair("EXPRESSION", "SIMPLE_EXPRESSION EXPRESSION_2"));
//
//       grammers.insert(make_pair("EXPRESSION_2" , "e"));
//
//       grammers.insert(make_pair("EXPRESSION_2" , "relop SIMPLE_EXPRESSION"));
//
//       grammers.insert(make_pair("SIMPLE_EXPRESSION" , "TERM SIMPLE_EXPRESSION_2")) ;
//
//       grammers.insert(make_pair("SIMPLE_EXPRESSION" ,"SIGN TERM SIMPLE_EXPRESSION_2" ));
//
//       grammers.insert(make_pair("SIMPLE_EXPRESSION_2" , "addop TERM SIMPLE_EXPRESSION_2"));
//
//       grammers.insert(make_pair("SIMPLE_EXPRESSION_2" , "e"));
//
//       grammers.insert(make_pair("TERM" , "FACTOR TERM_2"));
//
//       grammers.insert(make_pair("TERM_2" ,  "mulop FACTOR TERM_2"));
//
//       grammers.insert(make_pair("TERM_2" , "e"));
//
//       grammers.insert(make_pair("FACTOR" ,"id" ));
//
//       grammers.insert(make_pair("FACTOR" , "num"));
//
//       grammers.insert(make_pair("FACTOR" , "( EXPRESSION )"));
//
//
//       grammers.insert(make_pair("SIGN" , "+"));
//
//       grammers.insert(make_pair( "SIGN" , "-"));





}


















StartToParser::StartToParser()
{
    string tmp[] = {"id", ";","int" , "float","if", "(", ")", "{" , "}" , "else", "while" , "=" , "relop" , "addop" , "mulop" , "num" , "+" , "-", "e" };
    for (int i = 0; i < sizeof(tmp) / sizeof(tmp[0]); ++i)
    {
        terminals.insert(tmp[i]);
    }

}

StartToParser::~StartToParser()
{
    //dtor
}
