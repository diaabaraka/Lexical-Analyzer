#include "Parser.h"

Parser::Parser( string start,vector<string>*in,set<string>*t,map<string, map<string,string> > *table)
{


    start_symbol=start;
    inputs=*in;
    terminals=*t;
    parsing_table=*table;


}

Parser::~Parser()
{
    //dtor
}

void Parser::genParseTree()
{
    stack <string>symbols;  /* Contains grammar symbols. */


    string curr_input;      /* Contains current symbol of the input string. */

    symbols.push("$");                /* The special end marker symbol. */
    symbols.push(start_symbol);       /* The starting non terminal symbol. */

//    abdallah.getNext(curr_input);
    int xx=0;
    curr_input=inputs[xx];
    xx++;

    string top_of_stack;
    while(true)
    {
        top_of_stack=symbols.top();
        symbols.pop();
        if(top_of_stack.compare(curr_input)==0)
        {
            if(top_of_stack.compare("$")==0) /* Parser halts (successful completion) */
            {
                cout<<"Accept"<<endl;
                break;
            }
            else
            {
//                abdallah.getNext(curr_input);
                curr_input=inputs[xx];
                xx++;
            }

        }
        else
        {

            if(terminals.find(top_of_stack)==terminals.end())/* should be handled (top_of_stack is nonterminal)*/
            {
                map<string, map<string,string> >::iterator p;

                p=parsing_table.find(top_of_stack);
                if(p != parsing_table.end())
                {
                    map<string ,string>m=p->second;
                    map<string ,string>::iterator u;
                    u=m.find(curr_input);
                    if(u != m.end())
                    {
                        string prod_rule=u->second;
                        if(prod_rule.compare("sync")!=0){
                        cout<<p->first<<"--->"<<prod_rule<<endl;
                        istringstream iss(prod_rule);
                        vector<string> tokens;
                        copy(istream_iterator<string>(iss),
                             istream_iterator<string>(),back_inserter(tokens));

                        for(int i=tokens.size()-1; i>=0; i--)
                        {
                            symbols.push(tokens[i]);
                        }

                        }
                    }
                    else{

                         cout<<"ERROR :(illegal "<<top_of_stack<<" )-discard "<<curr_input<<endl;
                         symbols.push(top_of_stack);
                           curr_input=inputs[xx];
                xx++;

                    }

                }
            }
            else
            {
                cout<<"ERROR :missing "<<top_of_stack<<", inserted"<<endl;
                xx--;
            }

        }


    }




}
