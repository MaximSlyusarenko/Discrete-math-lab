#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

const int mod = 1000000007;
const int symbols = 25;
vector <int> term;
vector <int> from[200000][30];
long long dp[2000][200]; // dp[i][j] - сколько слов длины i можно получить, придя в состояние j

int main()
{
    freopen ("problem4.in", "r", stdin);
    freopen ("problem4.out", "w", stdout);
    int n, m, k, l;
    cin >> n >> m >> k >> l;
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
    dp[0][1] = 1;
    for (int i = 1; i < l + 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int p = 0; p <= symbols; p++)
            {
                vector <int> fr = from[j + 1][p];
                for (int q = 0; q < (int) fr.size(); q++)
                {
                    dp[i][j + 1] += dp[i - 1][fr[q]];
                    dp[i][j + 1] %= mod;
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < term.size(); i++)
    {
        ans += dp[l][term[i]];
        ans %= mod;
    }
    cout << ans << endl;
    return 0;
}