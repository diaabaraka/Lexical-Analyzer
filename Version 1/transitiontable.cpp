#include <iostream>
#include <fstream>
#include "string.h"
#include <map>
#include "State.h"
#include "NFA.h"
using namespace std;


string  keyWards [5] ;
map <char , string> FinalStates ;
map <char , int > Coulmns ;

bool isKeyWords (string token )
{
    int i ;
    for(i=0 ;  i < 5 ; i++)
    {
        if ( token.compare(keyWards[i])==0 )
        {

            return true ;

        }



    }
    return false ;

}


int main()
{

    State transitionTable [10][50]; //  will change to 2d array of object State (charachater  symbol , boolean accepting , string type )

    NFA nfa ;
    fstream fin ;

    fin.open("testProgram.txt", ios::in);

    char my_character ;

    string token ;

    string finalState ;

    State state = nfa .startState;

    while (!fin.eof() )
    {

        fin.get(my_character);

        if (my_character == ' ')
        {
            if (finalState !="" && token !="")
            {
                if(isKeyWords(token))
                {
                    cout<<token<<endl;

                }
                else
                {
                    cout << finalState ;
                }
                token ="";
                finalState="";

            }

        }
        else if (my_character==';'|| my_character==','||my_character=='(' ||my_character==')' || my_character =='{' || my_character== '}' )
        {
            if(finalState!=""&&token!="")
            {
                if(isKeyWords(token))
                {
                    cout << token << endl ;
                }
                else
                {
                    cout << finalState ;

                }
            }
            cout  << my_character << endl ;
            token= "";
            finalState = "";

        }
        else
        {

            token+=my_character+"";

            int indexForColom=0 ; // from hashtable of colums

            int indexForRow = state.get_Id(); //( state .symbol -'A' ) ;


            state  = transitionTable [indexForRow][indexForColom] ; // will change to object state

            if (state .isAccepting() == true )
            {
                finalState = state .getType() ;
            }



        }

    }


    return 0;
}
