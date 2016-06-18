#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

string p;
char pattern[2000002];
int z[2000002];

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
    ifstream in("z.in");
    ofstream out("z.out");
    in >> p;
    int m = (int) p.size();
    for (int i = 0; i < m; i++)
    {
        pattern[i] = p[i];
    }
    z_function(pattern, m);
    for (int i = 1; i < m; i++)
    {
        out << z[i] << " ";
    }
    return 0;
}