#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

struct vertex
{
    int length;
    int link;
    map <char, int> next;
    bool terminated;
};

vector <vertex> automaton;
int last;
string s;

int main()
{
    freopen ("automaton.in", "r", stdin);
    freopen ("automaton.out", "w", stdout);
    cin >> s;
    last = 0;
    vertex tmp;
    tmp.length = 0;
    tmp.link = -1;
    automaton.push_back(tmp);
    for (int i = 0; i < s.size(); i++)
    {
        int cur = (int) automaton.size();
        vertex current_vertex;
        current_vertex.length = automaton[last].length + 1;
        current_vertex.terminated = false;
        int p = last;
        while (p != -1 && automaton[p].next.find(s[i]) == automaton[p].next.end())
        {
            automaton[p].next[s[i]] = cur;
            p = automaton[p].link;
        }
        if (p == -1)
        {
            current_vertex.link = 0;
            automaton.push_back(current_vertex);
            last = cur;
            continue;
        }
        int q = automaton[p].next[s[i]];
        if (automaton[p].length + 1 == automaton[q].length)
        {
            current_vertex.link = q;
            automaton.push_back(current_vertex);
            last = cur;
            continue;
        }
        int clone = (int) (automaton.size() + 1);
        vertex clone_vertex;
        clone_vertex.link = automaton[q].link;
        clone_vertex.next = automaton[q].next;
        clone_vertex.length = automaton[p].length + 1;
        clone_vertex.terminated = false;
        while (p != -1 && automaton[p].next[s[i]] == q)
        {
            automaton[p].next[s[i]] = clone;
            p = automaton[p].link;
        }
        automaton[q].link = clone;
        current_vertex.link = clone;
        automaton.push_back(current_vertex);
        automaton.push_back(clone_vertex);
        last = cur;
    }
    int temp = last;
    while (temp != -1)
    {
        automaton[temp].terminated = true;
        temp = automaton[temp].link;
    }
    long long number_of_edges = 0;
    for (int i = 0; i < automaton.size(); i++)
    {
        number_of_edges += automaton[i].next.size();
    }
    cout << automaton.size() << " " << number_of_edges << endl;
    for (int i = 0; i < automaton.size(); i++)
    {
        for (map <char, int>::iterator it = automaton[i].next.begin(); it != automaton[i].next.end(); it++)
        {
            cout << i + 1 << " " << it -> second + 1 << " " << it -> first << endl;
        }
    }
    vector <int> terminated;
    for (int i = 0; i < automaton.size(); i++)
    {
        if (automaton[i].terminated)
        {
            terminated.push_back(i + 1);
        }
    }
    cout << terminated.size() << endl;
    for (int i = 0; i < terminated.size(); i++)
    {
        cout << terminated[i] << " ";
    }
    return 0;
}