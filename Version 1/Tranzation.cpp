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
#include <sstream>

#define SZ(V) (int)V.size()

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


void Tranzation:: read(){

  string line;
  ifstream myfile ("testProgram.txt");

  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
        //split
          vector<string> words = splitSpace(line);
         // cout<<"out od s\n";
          for(int i = 0 ; i < SZ(words) ; i++){


            parse(words[i]);


          }


    }
    myfile.close();
  }


return ;


}

vector<string> Tranzation:: splitSpace(string line ){


    string buf;
    stringstream ss(line);

    vector<string> tokens;

    while (ss >> buf)
        tokens.push_back(buf);


 return tokens;
}






void Tranzation::parse(string word){



//State* startState = NULL;

State* startState = dfaTable [0];





State* state =startState ;

string lastAccpeting ;



char my_character ;

string token ;

string finalState ;

vector<State*>nextStates;

int i = 0;
while (i < word.size()) {


	my_character = word[i];
    string yy = "";
    yy.push_back(my_character);
    //cout<<my_character<<" in the loop"<<endl;
	if (my_character=='\n')
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
	  else{
        cout<<"error"<<endl;
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
	  else{
        cout<<"error"<<endl;
	  }

	         cout << my_character << " does not exist in the scope of the language " << endl ;

	         string seend= word.substr(i+1,word.length()-(i+1));
               // cout << "seeend when error   " << seend << endl;
                parse(seend);

                return ;



       return  ;
    }



	state->getTrasitions(yy, nextStates);



	if(nextStates.size()==0)
	{

	        if(state->get_Id()==startState->get_Id())
            {
                cout<<"error "<< endl;

                string seend= word.substr(i+1,word.length()-(i+1));
               // cout << "seeend when error   " << seend << endl;
                parse(seend);

                return ;
            }
            if(state->isAccepting()==false)
            {
                // what if there is no previous AC
                if(finalState == ""){
                    cout<< "error" << endl;
                }
                else
               cout << finalState << endl ;


               string send = word.substr(i,word.length()-i);

               parse(send);
               return ;



            }
     // here no transiation from acceptingState
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
           cout<<"error " <<   endl ;

           string seend= word.substr(i+1,word.length()-(i+1));
            //cout << "seeend when error 2  " << seend << endl;
                parse(seend);

                return ;

	     }

	     state = nextStates[0];

	     if(state->isAccepting())
         {
            finalState=state->getType();

            lastAccpeting=token ;

         }




	   }



	}else
	{
       token.push_back(my_character);

        state= nextStates[0];


	    if (state ->isAccepting() == true )
	    {

	      finalState = state ->getType() ;
           lastAccpeting=token ;

	    }

     }

   }
    i++;
}




	  if (finalState !="" && token !="")
	  {

	    if(isKeyWords(token)||isPunctuation(token))
	    {
	       cout<<token<<endl;

	    }else
	    {
	        if(state->isAccepting()==false)
            {
               cout << finalState << endl ;


               string send = word.substr(lastAccpeting.length(),word.length()-lastAccpeting.length());
              // cout << "lAstAcceptin "<<lastAccpeting<<endl;
              // cout << "seeeend "<< send <<  endl ;
               parse(send);
               return ;



            }
	      cout << finalState<<endl ;
	    }


	  }

	  else{
       // cout<<"error"<<endl;
	  }
return ;



}



//void Tranzation:: parse()
//{
//
//
//}





Tranzation::~Tranzation()
{
    //dtor
}
