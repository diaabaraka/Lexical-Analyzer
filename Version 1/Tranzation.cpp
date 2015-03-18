#include <iostream>
#include <fstream>
#include <set>
#include "Tranzation.h"
#include <string>
#include <stack>
#include <map>
#include <deque>
#include <vector>
#include <set>
#include <algorithm>
#include <list>


using namespace std;

set<string>inputScope ;

vector<State*>dfaTable;

set<string>kWards;

set<string>punctuation ;

Tranzation::Tranzation(set <string> input , vector <State*>states , set<string>keys , set <string>pun)
{
    inputScope=input ;
    states=dfaTable ;
    kWards=keys;
    punctuation=pun;

}


//string keys[30] ={ "sizeof",  "struct", "class",  "static", "return", "void", "protected" , "private",  "public",  "case"
//, "break", "short", "int" , "if" , "else" , "while" , "for" ,"elseif" , "string" , "char",
//"long"  ,   "bool"  , "true" , "false" , "switch" , "new" , "try" , "auto" , "float" , "catch"};

bool Tranzation:: isKeyWords (string token )
{

    return (kWards.find(token)!=inputScope.end());


}

bool Tranzation :: isPunctuation(string s)
{

   return (punctuation.find(s)!=inputScope.end());


}




void Tranzation:: parse()
{



State* startState = dfaTable [0];

State* state =startState ;


fstream fin ;

fin.open("testProgram.txt", ios::in);

char my_character ;

string token ;

string finalState ;

vector<State*>nextStates;


while (!fin.eof() ) {

	fin.get(my_character);

    bool is_out = (inputScope.find(my_character+"")==inputScope.end());

    if(is_out)
    {
       cout << my_character << " is not exist in the scope of the language " << endl ;
       return  ;
    }


	if (my_character == ' ')
	{
	  if (finalState !="" && token !="")
	  {
	    if(isKeyWords(token))
	    {
	       cout<<token<<endl;

	    }else
	    {
	      cout << finalState ;
	    }
	    token ="";
	    finalState="";
	    state =startState ;

	  }

	}else if (isPunctuation(my_character+"") )
	{
	   if(finalState!=""&&token!="")
	   {
	       if(isKeyWords(token))
	      {
	         cout << token << endl ;
	      }else
	      {
	        cout << finalState ;

	      }
	   }
	   cout  << my_character << endl ;
	   token= "";
	   finalState ="";
	   state=startState ;

	}else
	{

	   token+=my_character+"";



	state->getTrasitions(my_character+"", nextStates);



	if(nextStates.size()==0)
	{

	   if (finalState!=""&&token!="")
	   {
	      if(isKeyWords(token))
	      {
	         cout<<token << endl ;

	      }else
	      {

	         cout <<finalState <<endl ;

	      }

	      finalState = "" ;

	      state =startState ;



	   }



	}else
	{

        state= nextStates[0];


	    if (state ->isAccepting() == true )
	    {
	      finalState = state ->getType() ;
	    }

     }

   }

}










}





Tranzation::~Tranzation()
{
    //dtor
}
