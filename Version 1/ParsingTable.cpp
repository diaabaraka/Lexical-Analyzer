#include "ParsingTable.h"
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
#include <iostream>
#include <cstdio>
#include <map>
#include <set>
using namespace std;


 map<string,map<string,string> > ParsingTable::getFinalTable(){
  return finalTable;
 }


void ParsingTable::findSync(multimap<string,string> follow_map,set <string> allTerminals,bool error){

 if(error) {
        cout<<"ambiguity detected"<<endl;
  return;
 }

  map <string,map <string,string> >::iterator its;

  for (its=finalTable.begin(); its!=finalTable.end();its=finalTable.upper_bound(its->first)){

     string nonTerminal=its->first;

     map<string,string>mmm= its->second;


         for (set<string>::iterator it=allTerminals.begin(); it!=allTerminals.end(); ++it){

   bool found=false;

    if(!mmm.count(*it)){


         multimap<string,string>::iterator itFollow;   //// iterate on first_map


    for (itFollow=follow_map.equal_range(nonTerminal).first; itFollow!=follow_map.equal_range(nonTerminal).second; ++itFollow)  // last loop and check for epsilon
        {

      string terminal=(*itFollow).second;

       if(terminal==*it){


        found=true;

       }

        }

                }

       if(found){

        if(finalTable.count(nonTerminal)){

            if(finalTable.find(nonTerminal)->second.count(*it)){
      // do nothing
  }
   else{

    finalTable.find(nonTerminal)->second[*it]="sync";

   }

        }

        else{
         map<string,string>mm;
         mm[*it]="sync";
          finalTable[nonTerminal]=mm;

        }
              }
                }
          }


 cout<<endl;

     // map <string,map <string,string> >::iterator its;

  for (its=finalTable.begin(); its!=finalTable.end();its=finalTable.upper_bound(its->first)){

  cout<<its->first<<"   " ;

 map<string,string>mmm= its->second;

   for (set<string>::iterator it=allTerminals.begin(); it!=allTerminals.end(); ++it){


            if(mmm.count(*it)){
             cout<<*it<<":"<<mmm.find(*it)->second<<"      ";
            }


  }
  cout<<endl;
  cout<<"______________________________________________________________________";
  cout<<endl;
  cout<<endl;
  }


return;

}




ParsingTable::ParsingTable(multimap<string,string> rules,multimap<string,string> first_map ,multimap<string,string> follow_map,  set<string> allNonTerminals)
{


   bool Error=false;



// rules.insert(make_pair("E","TE'"));
// rules.insert(make_pair("E'","+TE'"));
//
//rules.insert(make_pair("E'","e"));
//
// rules.insert(make_pair("T","FT'"));
// rules.insert(make_pair("T'","*FT'"));
// rules.insert(make_pair("T'","e"));
// rules.insert(make_pair("F","(E)"));
// rules.insert(make_pair("F","id"));
//
//
//first_map.insert(make_pair("TE'","("));
//first_map.insert(make_pair("TE'","id"));
//first_map.insert(make_pair("+TE'","+"));
//first_map.insert(make_pair("e","e"));
//first_map.insert(make_pair("FT'","("));
//first_map.insert(make_pair("FT'","id"));
//first_map.insert(make_pair("*FT'","*"));
//first_map.insert(make_pair("(E)","("));
//first_map.insert(make_pair("id","id"));
//
//follow_map.insert(make_pair("E","$"));
//follow_map.insert(make_pair("E",")"));
//follow_map.insert(make_pair("E'","$"));
//follow_map.insert(make_pair("E'",")"));
//follow_map.insert(make_pair("T","+"));
//follow_map.insert(make_pair("T",")"));
//follow_map.insert(make_pair("T","$"));
//follow_map.insert(make_pair("T'","+"));
//follow_map.insert(make_pair("T'",")"));
//follow_map.insert(make_pair("T'","$"));
//
//follow_map.insert(make_pair("F","+"));
//follow_map.insert(make_pair("F",")"));
//follow_map.insert(make_pair("F","$"));
//follow_map.insert(make_pair("F","*"));




//follow_map.insert(make_pair("E","*"));   // for sync purpose



  multimap<string,string>::iterator it;

      for (it=rules.begin(); it!=rules.end();it=rules.upper_bound(it->first)){


    string nonTerminal=it->first;


    multimap<string,string>::iterator it2;

     string goingTo;

    for (it2=rules.equal_range(nonTerminal).first; it2!=rules.equal_range(nonTerminal).second; ++it2)
        {

//      cout << ' ' << (*it2).second;
//       cout << '\n';

      goingTo=(*it2).second;


      multimap<string,string>::iterator itFirst;   //// iterate on first_map


   bool foundEpsilon=false;

    for (itFirst=first_map.equal_range(goingTo).first; itFirst!=first_map.equal_range(goingTo).second; ++itFirst)  // last loop and check for epsilon
        {

      string terminal=(*itFirst).second;

       if(terminal=="e")foundEpsilon=true;

//        hm2[terminal]=goingTo;

 if(finalTable.count(nonTerminal)){   // is this non termial exists ??? or not

  if(finalTable.find(nonTerminal)->second.count(terminal)){
        Error=true;
  }
else{
    finalTable.find(nonTerminal)->second[terminal]=goingTo;
}

  }

else{
    map <string,string> hm2;
   hm2[terminal]=goingTo;
   finalTable[nonTerminal]=hm2;
    }

        }

  //  finalTable[nonTerminal]=hm2;




 bool foundDollarSign=false;

  if(foundEpsilon){   // then add follow




       multimap<string,string>::iterator itFollow;   //// iterate on first_map


    for (itFollow=follow_map.equal_range(nonTerminal).first; itFollow!=follow_map.equal_range(nonTerminal).second; ++itFollow)  // last loop and check for epsilon
        {

      string terminal=(*itFollow).second;


       if(terminal=="$")foundDollarSign=true;


       if(finalTable.count(nonTerminal)){   // is this non termial exists ??? or not


if(finalTable.find(nonTerminal)->second.count(terminal)){
        Error=true;

  }
else{

    finalTable.find(nonTerminal)->second[terminal]=goingTo;


}

  }


else{
    map <string,string> hm3;
   hm3[terminal]=goingTo;
   finalTable[nonTerminal]=hm3;
    }


            }

              }


 if(foundDollarSign){

    if(finalTable.count(nonTerminal)){   // is this non termial exists ??? or not

if(finalTable.find(nonTerminal)->second.count("$")){
      //  Error=true;

  }

else{
    finalTable.find(nonTerminal)->second["$"]=goingTo;
}
  }


else{
    map <string,string> hm3;
   hm3["$"]=goingTo;
   finalTable[nonTerminal]=hm3;
    }

 }

        }


      }



  findSync(follow_map,allNonTerminals,Error);






}

ParsingTable::~ParsingTable()
{
    //dtor
}
