#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

string t, p;
char text[2000002], pattern[2000002];
int z[2000002];
vector <int> ans;

void z_function(char* pattern, int n)
{
    int left = 0;
    int right = 0;
    for (int i = 1; i < n; i++)
    {
        z[i] = max(0, min(right - i, z[i - left]));
        while (i + z[i] < n && pattern[z[i]] == pattern[i + z[i]])
        {
            z[i]++;
        }
        if (i + z[i] >= right)
        {
            left = i;
            right = i + z[i];
        }
    }
}

int main()
{
    ifstream in("search2.in");
    ofstream out("search2.out");
    in >> p >> t;
    int m = (int) p.size();
    int n = (int) t.size();
    for (int i = 0; i < m; i++)
    {
        pattern[i] = p[i];
    }
    pattern[m] = '#';
    for (int i = 0; i < t.size(); i++)
    {
        pattern[m + i + 1] = t[i];
    }
    z_function(pattern, m + n + 1);
    for (int i = m + 1; i < m + n + 1; i++)
    {
        if (z[i] == m)
        {
            ans.push_back(i - m);
        }
    }
    out << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        out << ans[i] << " ";
    }
    return 0;
}