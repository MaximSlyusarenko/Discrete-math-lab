#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

bool term[200000];
int to[200000][30];

int main()
{
    freopen ("problem1.in", "r", stdin);
    freopen ("problem1.out", "w", stdout);
    string s;
    cin >> s;
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        term[i + 1] = false;
        for (int j = 0; j < 28; j++)
        {
            to[i + 1][j] = 0;
        }
    }
    for (int i = 0; i < k; i++)
    {
        int tmp;
        cin >> tmp;
        term[tmp] = true;
    }
    for (int i = 0; i < m; i++)
    {
        int from, t;
        char c;
        cin >> from >> t >> c;
        to[from][c - 'a'] = t;
    }
    int  size = (int) s.size();
    int current = 1;
    for (int i = 0; i < size; i++)
    {
        if (to[current][s[i] - 'a'] == 0)
        {
            cout << "Rejects" << endl;
            return 0;
        }
        else
        {
            current = to[current][s[i] - 'a'];
        }
    }
    if (term[current])
    {
        cout << "Accepts" << endl;
    }
    else
    {
        cout << "Rejects" << endl;
    }
    return 0;
}