#ifndef TRANZATION_H
#define TRANZATION_H
#include "string.h"
#include <map>
#include <set>
#include "State.h"
#include "NFA.h"
#include "Controller.h"
#include "DFA.h"
#include "Tranzation.h"
#include <set>



class Tranzation
{
    public:
        Tranzation(set <string> input , vector <State*>states ,  set<string>keys ,set <string>pun );
        virtual ~Tranzation();
        void read();
        vector<string> splitSpace(string line );
     set<string>inputScope ;

     vector<State*>dfaTable;

     set<string>kWards ;
     set<string> punctuation ;





     bool  isKeyWords (string token );
     bool  isPunctuation(string s);


     void  parse(string word);

    protected:

    private:
};

#endif // TRANZATION_H
