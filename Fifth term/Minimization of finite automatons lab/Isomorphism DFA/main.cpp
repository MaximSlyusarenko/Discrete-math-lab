#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>

using namespace std;

int n1, m1, k1, n2, m2, k2;
int to1[200000][30], to2[200000][30];
bool is_term1[200000], is_term2[200000];
bool used1[200000], used2[200000];
string answer;

void dfs(int v1, int v2)
{
    used1[v1] = true;
    used2[v2] = true;
    if (is_term1[v1] != is_term2[v2])
    {
        answer = "NO";
    }
    for (int i = 0; i < 26; i++)
    {
        if (to1[v1][i] != -1 && to2[v2][i] != -1)
        {
            if (!used1[to1[v1][i]] && !used2[to2[v2][i]])
            {
                dfs(to1[v1][i], to2[v2][i]);
            }
            else if (!used1[to1[v1][i]] || !used2[to2[v2][i]])
            {
                answer = "NO";
            }
        }
        else if (to1[v1][i] != -1 || to2[v2][i] != -1)
        {
            answer = "NO";
        }
    }
}

int main()
{
    freopen ("isomorphism.in", "r", stdin);
    freopen ("isomorphism.out", "w", stdout);
    answer = "YES";
    cin >> n1 >> m1 >> k1;
    for (int i = 0; i < n1; i++)
    {
        is_term1[i + 1] = false;
        is_term2[i + 1] = false;
        used1[i + 1] = false;
        used2[i + 1] = false;
        for (int j = 0; j < 26; j++)
        {
            to1[i + 1][j] = -1;
            to2[i + 1][j] = -1;
        }
    }
    for (int i = 0; i < k1; i++)
    {
        int a;
        cin >> a;
        is_term1[a] = true;
    }
    for (int i = 0; i < m1; i++)
    {
        int a, b;
        char c;
        cin >> a >> b >> c;
        to1[a][c - 'a'] = b;
    }
    cin >> n2 >> m2 >> k2;
    if (n1 != n2 || m1 != m2 || k1 != k2)
    {
        cout << "NO" << endl;
        return 0;
    }
    for (int i = 0; i < k2; i++)
    {
        int a;
        cin >> a;
        is_term2[a] = true;
    }
    for (int i = 0; i < m2; i++)
    {
        int a, b;
        char c;
        cin >> a >> b >> c;
        to2[a][c - 'a'] = b;
    }
    dfs(1, 1);
    cout << answer << endl;
    return 0;
}