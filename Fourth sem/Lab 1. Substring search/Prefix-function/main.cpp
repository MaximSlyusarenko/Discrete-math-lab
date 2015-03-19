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
    ifstream in("prefix.in");
    ofstream out("prefix.out");
    in >> s;
    prefix_function(s);
    for (int i = 0; i < s.size(); i++)
    {
        out << prefix[i] << " ";
    }
    return 0;
}