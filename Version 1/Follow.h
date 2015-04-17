#ifndef FOLLOW_H_INCLUDED
#define FOLLOW_H_INCLUDED

class Follow {
public:
	Follow();
	void getTrasitions(string input,vector<string>&dest);
	set<string> getFollow(string name);
	vector<string> splitSpace(string line);
	multimap<string , string> getAllFollow();
	bool contains(string x , string y);

private:
    First first;
	StartToParser obj;
	multimap <string, string> expression_follow;
	map<string, set<string> > follows;

	bool add_to_follow(string non_terminal, set<string> arr);

	map<string, set<string> > grammer;

	vector<vector<int> > graph;
	map<string, int> non_terminal;
	vector<string> non_terminal1;

	void bfs(int src);

	multimap<string, string> to_multimap();

};

#endif // FOLLOW_H_INCLUDED
