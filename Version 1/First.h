/*
 * First.h
 *
 *  Created on: Apr 15, 2015
 *      Author: mostfa
 */

#ifndef FIRST_H_
#define FIRST_H_

#include <map>
#include <string>
#include "StartToParser.h"
class First {
public:
	First();
	void getTrasitions(string input,vector<string>&dest);
	set<string> getFirst(string name);
	vector<string> splitSpace(string line);
	multimap<string , string> getAllFirst();
	bool contains(string x , string y);
	virtual ~First();


private:
	StartToParser obj;
	multimap <string, string>expression_First;
};

#endif /* FIRST_H_ */
