#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

int n1, m1, k1, n2, m2, k2;
int to1[200000][30], to2[200000][30];
bool is_term1[200000], is_term2[200000];
bool used1[200000], used2[200000];
queue <pair <int, int> > q;

int main()
{
    freopen ("equivalence.in", "r", stdin);
    freopen ("equivalence.out", "w", stdout);
    cin >> n1 >> m1 >> k1;
    for (int i = 0; i < n1; i++)
    {
        is_term1[i + 1] = false;
        used1[i + 1] = false;
        for (int j = 0; j < 26; j++)
        {
            to1[i + 1][j] = 0; // 0 - fake vertex, in which goes all edges which isn't exists. All edges from 0 goes to 0. So, if we have an edge in first automaton and haven't in second, we will only understand, can we go to terminate vertex after going on this edge in second.
        }
    }
    is_term1[0] = false;
    used1[0] = false;
    for (int j = 0; j < 26; j++)
    {
        to1[0][j] = 0;
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
    for (int i = 0; i < n2; i++)
    {
        is_term2[i + 1] = false;
        used2[i + 1] = false;
        for (int j = 0; j < 26; j++)
        {
            to2[i + 1][j] = 0;
        }
    }
    is_term2[0] = false;
    used2[0] = false;
    for (int j = 0; j < 26; j++)
    {
        to2[0][j] = 0;
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
    q.push(make_pair(1, 1));
    used1[1] = true;
    used2[1] = true;
    while (!q.empty())
    {
        pair <int, int> current_vertexes = q.front();
        q.pop();
        int vertex1 = current_vertexes.first;
        int vertex2 = current_vertexes.second;
        if (is_term1[vertex1] != is_term2[vertex2])
        {
            cout << "NO" << endl;
            return 0;
        }
        for (int i = 0; i < 26; i++)
        {
            if ((!used1[to1[vertex1][i]] || !used2[to2[vertex2][i]]) && (to1[vertex1][i] != 0 || to2[vertex2][i] != 0))
            {
                q.push(make_pair(to1[vertex1][i], to2[vertex2][i]));
                if (to1[vertex1][i] != 0) // we can go to vertex 0 more than once
                {
                    used1[to1[vertex1][i]] = true;
                }
                if (to2[vertex2][i] != 0)
                {
                    used2[to2[vertex2][i]] = true;
                }
            }
        }
    }
    cout << "YES" << endl;
    return 0;
}