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
    dfaTable=states ;
    kWards=keys;
    punctuation=pun;

//        set<string, State*>::iterator iter;
//
//        for (iter = inputScope.begin(); iter != inputScope.end(); ++iter) {
//
//            cout<<*iter<<endl;
//
//        }

    cout<<"finish construtor\n";
}


//string keys[30] ={ "sizeof",  "struct", "class",  "static", "return", "void", "protected" , "private",  "public",  "case"
//, "break", "short", "int" , "if" , "else" , "while" , "for" ,"elseif" , "string" , "char",
//"long"  ,   "bool"  , "true" , "false" , "switch" , "new" , "try" , "auto" , "float" , "catch"};

bool Tranzation:: isKeyWords (string token )
{

    return (kWards.find(token)!=kWards.end());


}

bool Tranzation :: isPunctuation(string s)
{

   return (punctuation.find(s)!=punctuation.end());


}




void Tranzation:: parse()
{

cout<<"int table\n";

//State* startState = NULL;

State* startState = dfaTable [0];

cout<<"int table\n";



State* state =startState ;



fstream fin ;

fin.open("testProgram.txt", ios::in);

char my_character ;

string token ;

string finalState ;

vector<State*>nextStates;


while (!fin.eof() ) {

	fin.get(my_character);
	if( fin.eof() )
        break;
    string yy = "";
    yy.push_back(my_character);
    //cout<<my_character<<" in the loop"<<endl;
	if (my_character == ' '||my_character=='\n')
	{


	  if (finalState !="" && token !="")
	  {
	    if(isKeyWords(token))
	    {
	       cout<<token<<endl;

	    }else
	    {
	      cout << finalState << endl  ;
	    }
	    token ="";
	    finalState="";
	    state =startState ;


	  }

	}else if (isPunctuation(yy) )
	{


	   if(finalState!=""&&token!="")
	   {
	       if(isKeyWords(token))
	      {
	         cout << token << endl ;
	      }else
	      {
	        cout << finalState <<endl ;

	      }
	   }
	   cout  << my_character << endl ;
	   token= "";
	   finalState ="";
	   state=startState ;


	}else
	{

	      bool is_out = (inputScope.find(yy)==inputScope.end());

    if(is_out)
    {

       if (finalState !="" && token !="")
	  {

	    if(isKeyWords(token)||isPunctuation(token))
	    {
	       cout<<token<<endl;

	    }else
	    {
	      cout << finalState<<endl ;
	    }


	  }

	         cout << my_character << " is not exist in the scope of the language " << endl ;

       return  ;
    }








	state->getTrasitions(yy, nextStates);







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
	      token=yy;

	     startState ->getTrasitions(yy,nextStates );
	     if(nextStates.empty()){
           cout<<"error " << endl ;
           return ;
	     }
	     state = nextStates[0];

	     if(state->isAccepting())
         {
            finalState=state->getType();

         }




	   }



	}else
	{
       token.push_back(my_character);

        state= nextStates[0];


	    if (state ->isAccepting() == true )
	    {

	      finalState = state ->getType() ;

	    }

     }

   }

}




	  if (finalState !="" && token !="")
	  {

	    if(isKeyWords(token)||isPunctuation(token))
	    {
	       cout<<token<<endl;

	    }else
	    {
	      cout << finalState<<endl ;
	    }


	  }


}





Tranzation::~Tranzation()
{
    //dtor
}
