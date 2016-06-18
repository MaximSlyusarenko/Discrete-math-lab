#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cstdio>

using namespace std;

struct vertex
{
    vector <char> edges;
    vector <int> to;
};

string s;
vector <vertex> trie;

int main()
{
    freopen ("trie.in", "r", stdin);
    freopen ("trie.out", "w", stdout);
    cin >> s;
    vertex root;
    trie.push_back(root);
    for (int i = 0; i < s.size(); i++)
    {
        int curr = 1;
        for (int j = i; j < s.size(); j++)
        {
            bool is = false;
            for (int k = 0; k < trie[curr - 1].to.size(); k++)
            {
                if (s[j] == trie[curr - 1].edges[k])
                {
                    curr = trie[curr - 1].to[k];
                    is = true;
                    break;
                }
            }
            if (!is)
            {
                vertex tmp;
                trie[curr - 1].edges.push_back(s[j]);
                trie[curr - 1].to.push_back(trie.size() + 1);
                trie.push_back(tmp);
                curr = trie.size();
            }
        }
    }
    cout << trie.size() << " " << trie.size() - 1 << endl;
    for (int i = 0; i < trie.size(); i++)
    {
        for (int j = 0; j < trie[i].edges.size(); j++)
        {
            int to = trie[i].to[j];
            char symb = trie[i].edges[j];
            cout << i + 1 << " " << to << " " << symb << endl;
        }
    }
    return 0;
}