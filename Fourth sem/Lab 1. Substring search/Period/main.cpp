#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <fstream>
#include <vector>

using namespace std;

string s;
int prefix[2000000];

void prefix_function(string s)
{
    prefix[0] = 0;
    for (int i = 1; i < s.size(); i++)
    {
        int k = prefix[i - 1];
        while (k > 0 && s[i] != s[k])
        {
            k = prefix[k - 1];
        }
        if (s[i] == s[k])
        {
            k++;
        }
        prefix[i] = k;
    }
}

int main()
{
    ifstream in("period.in");
    ofstream out("period.out");
    in >> s;
    prefix_function(s);
    int bord = prefix[s.size() - 1];
    int tmp = (int) s.size() - bord; // task 1 in fourth sem
    if (s.size() % tmp == 0)
    {
        out << tmp;
    }
    else
    {
        out << s.size();
    }
    return 0;
}