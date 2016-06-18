#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

vector <pair <string, string> > rules;
set <char> useless;
set <char> all_unterminals;
bool is_generating[1000];
bool is_reachable[1000];

int main()
{
    freopen ("useless.in", "r", stdin);
    freopen ("useless.out", "w", stdout);
    int n;
    string start;
    cin >> n >> start;
    for (int i = 0; i < n; i++)
    {
        string s1, s2, s3;
        cin >> s1;
        if (s1 == "->")
        {
            cin >> s3;
            s1 = rules[rules.size() - 1].second;
            rules[rules.size() - 1].second = "";
        }
        else
        {
            cin >> s2 >> s3;
        }
        rules.push_back(make_pair(s1, s3));
        all_unterminals.insert(s1[0]);
        for (int j = 0; j < s3.size(); j++)
        {
            if (s3[j] >= 'A' && s3[j] <= 'Z')
            {
                all_unterminals.insert(s3[j]);
            }
        }
    }
    for (int i = 0; i < 1000; i++)
    {
        is_generating[i] = false;
    }
    for (int i = 0; i < n; i++)
    {
        string left = rules[i].first;
        string right = rules[i].second;
        bool only_terminals = true;
        for (int j = 0; j < right.size(); j++)
        {
            if (right[j] < 'a' || right[j] > 'z')
            {
                only_terminals = false;
            }
        }
        if (only_terminals)
        {
            is_generating[left[0]] = true;
        }
    }
    bool added = true;
    while (added)
    {
        bool added_now = false;
        for (int i = 0; i < n; i++)
        {
            string left = rules[i].first;
            string right = rules[i].second;
            if (is_generating[left[0]])
            {
                continue;
            }
            bool new_generating = true;
            for (int j = 0; j < right.size(); j++)
            {
                if (right[j] >= 'A' && right[j] <= 'Z' && !is_generating[right[j]])
                {
                    new_generating = false;
                }
            }
            if (new_generating)
            {
                is_generating[left[0]] = true;
                added_now = true;
            }
        }
        added = added_now;
    }
    for (int i = 0; i < 26; i++)
    {
        if (!is_generating[i + 'A'] && all_unterminals.find(i + 'A') != all_unterminals.end())
        {
            useless.insert(i + 'A');
        }
    }
    for (int i = 0; i < 1000; i++)
    {
        is_reachable[i] = false;
    }
    is_reachable[start[0]] = true;
    added = true;
    while (added)
    {
        bool added_now = false;
        for (int i = 0; i < n; i++)
        {
            string left = rules[i].first;
            string right = rules[i].second;
            if (!is_reachable[left[0]])
            {
                continue;
            }
            bool new_reachable = false;
            for (int j = 0; j < right.size(); j++)
            {
                if (right[j] >= 'A' && right[j] <= 'Z')
                {
                    if (!is_reachable[right[j]])
                    {
                        is_reachable[right[j]] = true;
                        new_reachable = true;
                    }
                }
            }
            if (new_reachable)
            {
                added_now = true;
            }
        }
        added = added_now;
    }
    for (int i = 0; i < 26; i++)
    {
        if (!is_reachable[i + 'A'] && all_unterminals.find(i + 'A') != all_unterminals.end())
        {
            useless.insert(i + 'A');
        }
    }
    for (set <char>::iterator it = useless.begin(); it != useless.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}