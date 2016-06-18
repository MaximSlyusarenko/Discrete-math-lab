#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

int n, m, k;
bool is_term[2000];
int to[2000][30];
vector <int> reversed[2000][30];
bool used[2000];
bool marked[2000][2000] = {};
vector <char> symbols;

void dfs(int v)
{
    used[v] = true;
    for (int j = 0; j < 26; j++)
    {
        if (!used[to[v][j]])
        {
            dfs(to[v][j]);
        }
    }
}

int main()
{
    freopen ("minimization.in", "r", stdin);
    freopen ("minimization.out", "w", stdout);
    cin >> n >> m >> k;
    for (int i = 0; i <= n; i++)
    {
        is_term[i] = false;
        for (int j = 0; j < 26; j++)
        {
            to[i][j] = 0;
        }
    }
    for (int i = 0; i < k; i++)
    {
        int a;
        cin >> a;
        is_term[a] = true;
    }
    for (int i = 0; i < m; i++)
    {
        int a, b;
        char c;
        cin >> a >> b >> c;
        to[a][c - 'a'] = b;
        reversed[b][c - 'a'].push_back(a);
    }
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (to[i][j] == 0)
            {
                reversed[0][j].push_back(i);
            }
        }
    }
    for (int i = 0; i <= n; i++)
    {
        used[i] = false;
    }
    dfs(1);
    queue <pair <int, int> > q;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (!marked[i][j] && is_term[i] != is_term[j])
            {
                marked[i][j] = true;
                marked[j][i] = true;
                q.push(make_pair(i, j));
            }
        }
    }
    while (q.size() != 0)
    {
        pair <int, int> p = q.front();
        q.pop();
        for (int c = 0; c < 26; c++)
        {
            for (int i = 0; i < reversed[p.first][c].size(); i++)
            {
                for (int j = 0; j < reversed[p.second][c].size(); j++)
                {
                    if (!marked[reversed[p.first][c][i]][reversed[p.second][c][j]])
                    {
                        marked[reversed[p.first][c][i]][reversed[p.second][c][j]] = true;
                        marked[reversed[p.second][c][j]][reversed[p.first][c][i]] = true;
                        q.push(make_pair(reversed[p.first][c][i], reversed[p.second][c][j]));
                    }
                }
            }
        }
    }
    int component[2000];
    for (int i = 0; i <= n; i++)
    {
        component[i] = -1;
    }
    for (int i = 0; i <= n; i++)
    {
        if (!marked[0][i])
        {
            component[i] = 0;
        }
    }
    int number_of_components = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!used[i])
        {
            continue;
        }
        if (component[i] == -1)
        {
            number_of_components++;
            component[i] = number_of_components;
            for (int j = i + 1; j <= n; j++)
            {
                if (!marked[i][j])
                {
                    component[j] = number_of_components;
                }
            }
        }
    }
    int new_n = number_of_components;
    int new_m = 0, new_k = 0;
    int new_to[2000][30];
    for (int i = 1; i <= new_n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            new_to[i][j] = -1;
        }
    }
    bool new_is_term[2000];
    for (int i = 1; i <= n; i++)
    {
        for (int c = 0; c < 26; c++)
        {
            if (to[i][c] != 0 && component[to[i][c]] != 0)
            {
                new_to[component[i]][c] = component[to[i][c]];
            }
        }
    }
    for (int i = 1; i <= new_n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (new_to[i][j] != -1)
            {
                new_m++;
            }
        }
    }
    for (int i = 0; i <= new_n; i++)
    {
        new_is_term[i] = false;
    }
    for (int i = 1; i <= n; i++)
    {
        if (is_term[i])
        {
            new_is_term[component[i]] = true;
        }
    }
    for (int i = 1; i <= new_n; i++)
    {
        if (new_is_term[i])
        {
            new_k++;
        }
    }
    cout << new_n << " " << new_m << " " << new_k << endl;
    for (int i = 1; i <= new_n; i++)
    {
        if (new_is_term[i])
        {
            cout << i << " ";
        }
    }
    cout << endl;
    for (char i = 'a'; i <= 'z'; i++)
    {
        symbols.push_back(i);
    }
    for (int i = 1; i <= new_n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (new_to[i][j] != -1)
            {
                cout << i << " " << new_to[i][j] << " " << symbols[j] << endl;
            }
        }
    }
    return 0;
}