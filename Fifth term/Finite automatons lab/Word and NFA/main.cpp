#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

vector <int> term;
vector <int> from[200000][30];
bool dp[20000][200]; // перейти в состояние за n шагов

int main()
{
    freopen ("problem2.in", "r", stdin);
    freopen ("problem2.out", "w", stdout);
    string s;
    cin >> s;
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < s.size() + 2; j++)
        {
            dp[i + 1][j] = false;
        }
    }
    dp[0][1] = true;
    for (int i = 0; i < k; i++)
    {
        int tmp;
        cin >> tmp;
        term.push_back(tmp);
    }
    for (int i = 0; i < m; i++)
    {
        int fr, to;
        char c;
        cin >> fr >> to >> c;
        from[to][c - 'a'].push_back(fr);
    }
    int  size = (int) s.size();
    for (int i = 1; i < size + 1; i++)
    {
        char c = s[i - 1];
        for (int j = 0; j < n; j++)
        {
            vector <int> fr = from[j + 1][c - 'a'];
            bool can = false;
            for (int k = 0; k < fr.size() && !can; k++)
            {
                can |= dp[i - 1][fr[k]];
            }
            dp[i][j + 1] = can;
        }
    }
    for (int i = 0; i < k; i++)
    {
        if (dp[size][term[i]])
        {
            cout << "Accepts" << endl;
            return 0;
        }
    }
    cout << "Rejects" << endl;
    return 0;
}