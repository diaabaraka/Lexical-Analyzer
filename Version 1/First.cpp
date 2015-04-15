/*
 * First.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: mostfa
 */

#include "First.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <sstream>
#include "StartToParser.h"

using namespace std;

#define FOR(i, a, b) for(int i = (a); i < (b); ++i)
#define RFOR(i, b, a) for(int i = (b) - 1; i >= (a); --i)
#define REP(i, N) FOR(i, 0, N)
#define RREP(i, N) RFOR(i, N, 0)
First::First() {
	// TODO Auto-generated constructor stub
	obj.fillGrammerList();
	set<string>visited;
    multimap<string, string>::iterator st;

    for(st = obj.grammers.begin(); st != obj.grammers.end(); ++st){

    	if(visited.find(st->first) == visited.end()){

    		visited.insert(st->first);
    		set<string> res = getFirst(st->first);
    			set<string>::iterator iter;

    		for (iter = res.begin(); iter != res.end(); ++iter) {

    			//cout << (*iter) << endl;

    			expression_First.insert(make_pair(st->first , (*iter)));



    		}







    	}


    }


}
vector<string> First:: splitSpace(string line ){


    string buf;
    stringstream ss(line);

    vector<string> tokens;

    while (ss >> buf)
        tokens.push_back(buf);


 return tokens;
}

void First:: getTrasitions(string input,vector<string>&dest)
{
    dest.clear();
    multimap<string, string>::iterator st;

    for(st = obj.grammers.lower_bound(input); st != obj.grammers.upper_bound(input); ++st){
        dest.push_back(st->second);
        //cout<<st->second<<endl;
    }
}

set<string>First:: getFirst(string name){


	// first get all the parts of the expression from the map..
	// map contains all the parts of the expression
	// ex: x =:: yy gg | g
	// then the value coressponding to x in the map equals :(yy gg) and (g)


	vector<string> parts;
	getTrasitions(name , parts);
	set<string> result;
	REP(i , parts.size()){

		// get the parts and evaluate the first for each part
		string expr = parts[i];
		// split the expr using space char
		vector<string> splitted_expr = splitSpace(expr);


		REP(j , splitted_expr.size()){

			string word = splitted_expr[j];
			//cout<<word<<"\n";

			//cout<< word << endl;
			if(obj.terminals.find(word) != obj.terminals.end()){
				// found terminal word .. add it to the set and exit
				//cout<<"here22\n";
				result.insert(word);
				expression_First.insert(make_pair(expr , word));
				break;

			}
			else{
				// found non terminal word... so we need to find the first for this word and
				// add it to the result set
				set<string>tmp_res = getFirst(word);
				set<string>::iterator iter;

				for (iter = tmp_res.begin(); iter != tmp_res.end(); ++iter) {

					expression_First.insert(make_pair(expr , (*iter)));

					result.insert(*iter);

				}
				if(tmp_res.find("e") == tmp_res.end()){
					break;

				}



			}




		}




	}


	return result;



}

multimap<string , string> First:: getAllFirst(){
	return expression_First;
}


First::~First() {
	// TODO Auto-generated destructor stub
}
