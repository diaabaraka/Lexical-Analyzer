
#include "Follow.h"


using namespace std;

Follow::Follow()
{
    obj.fillGrammerList();
    multimap <string, string> temp = obj.grammers;

    multimap<string, string>::iterator it;
    int index = 0;
    for(it = temp.begin(); it != temp.end(); ++it)
    {
        string f = it->first;
        if(grammer.find(f)==grammer.end())
        {
            set<string> s;
            s.insert(it->second);
            grammer[f] = s;

            non_terminal1.push_back(f);
            non_terminal[f] = index++;

            set<string> b;
            follows[f] = b;
        }
        else
        {
            grammer[f].insert(it->second);
        }
    }

    for(int i=0; i<index; i++)
    {
        vector<int> a;
        graph.push_back(a);
    }

    follows[obj.startingSymbol].insert("$");

    expression_follow = get_follows();
}



bool Follow::add_to_follow(string non_terminal, set<string> arr)
{
    set<string> fllw = follows[non_terminal];
    set<string>::iterator it;
    bool flag = false;
    for(it = arr.begin(); it!=arr.end(); it++)
    {
        if(*it == "e")
            flag = true;
        else
            fllw.insert(*it);
    }
    follows[non_terminal] = fllw;
    return flag;
}

set<string> Follow::getFollow(string s)
{
    return follows[s];
}
multimap<string , string> Follow::getAllFollow()
{
    return expression_follow;
}

multimap<string , string> Follow::get_follows()
{

    map<string, set<string> >::iterator it;

    for(it = grammer.begin(); it != grammer.end(); ++it)
    {
        set<string> rhs_set = it->second;
        for(set<string>::iterator sit = rhs_set.begin(); sit!=rhs_set.end(); sit++)
        {

            vector<string> rhs = first.splitSpace(*sit);
            string cur, next;
            int len = (int)rhs.size();
            for(int i= 0; i<len; i++)
            {
                cur = rhs[i];
                if(obj.terminals.find(cur) != obj.terminals.end())
                    continue;

                if(i==len-1) // case 3) S -> A, then follow(A) = follow(S)
                {
                    graph[non_terminal[it->first]].push_back(non_terminal[cur]);//mapping to int
                }
                else   // case 1, 2
                {
                    next = rhs[i+1];
                    if(obj.terminals.find(next) != obj.terminals.end())  // 1) if next is terminal
                    {
                        follows[cur].insert(next);
                    }
                    else   // 2) if next is non-terminal
                    {
                        int idx = i+1;
                        bool flag = false;
                        while(flag=add_to_follow(cur, first.getFirst(next)))
                        {
                            if(idx+1 == len)
                                break;
                            next = rhs[++idx];
                        }
                        if(flag)  // case 3
                        {
                            graph[non_terminal[it->first]].push_back(non_terminal[cur]);
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < (int)graph.size(); i++)
        bfs(i);

    return to_multimap();
}

multimap<string, string> Follow::to_multimap()
{
    expression_follow.clear();
    for(map<string, set<string> >::iterator it = follows.begin(); it != follows.end(); ++it)
    {
        set<string> rhs_set = it->second;
        for(set<string>::iterator sit = rhs_set.begin(); sit!=rhs_set.end(); sit++)
        {
            expression_follow.insert(make_pair(it->first, *sit));
        }
    }
    return expression_follow;
}


void Follow::bfs(int src)
{
    queue<int> q;
    int len;
    int vst[len=non_terminal.size()];
    for(int i=0; i<len; i++) vst[i]=0;
    q.push(src);
    vst[src]=1;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int i = 0; i<graph[u].size(); i++)
        {
            int v = graph[u][i];
            if(!vst[v])
            {
                vst[v]=1;
                q.push(v);
                add_to_follow(non_terminal1[v], follows[non_terminal1[u]]);
            }
        }
    }

}



void Follow::printAll()
{
    for(map<string, set<string> >::iterator it = follows.begin(); it != follows.end(); ++it)
    {
        cout << it->first<< " = { ";
        set<string> rhs_set = it->second;
        for(set<string>::iterator sit = rhs_set.begin(); sit!=rhs_set.end(); sit++)
        {
            cout << *sit<<"  ";
        }
        cout << " }\n";
    }
}


