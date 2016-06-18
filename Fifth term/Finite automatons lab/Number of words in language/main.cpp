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
long long dp[200000]; //  dp[i] - сколько слов можно получить, дойдя до состояния i
long long dp2[200000]; // Нужен, чтобы проверить наличие цикла, из которого можно добраться до терминального состояния

int main()
{
    freopen ("problem3.in", "r", stdin);
    freopen ("problem3.out", "w", stdout);
    int n, m, k;
    cin >> n >> m >> k;
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
    dp[1] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= symbols; j++)
        {
            vector <int> fr = from[i + 1][j];
            for (int l = 0; l < (int) fr.size(); l++)
            {
                dp[i + 1] += dp[fr[l]];
                dp[i + 1] %= mod;
            }
        }
    }
    dp2[1] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= symbols; j++)
        {
            vector <int> fr = from[i + 1][j];
            for (int l = 0; l < (int) fr.size(); l++)
            {
                dp2[i + 1] += max(dp[fr[l]], dp2[fr[l]]); // Если нет цикла, описанного выше, то dp и dp2 будут одинаковыми после завершения программы
                dp2[i + 1] %= mod;
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < term.size(); i++)
    {
        if (dp2[term[i]] != dp[term[i]])
        {
            cout << -1 << endl;
            return 0;
        }
        ans += dp[term[i]];
        ans %= mod;
    }
    cout << ans << endl;
    return 0;
}