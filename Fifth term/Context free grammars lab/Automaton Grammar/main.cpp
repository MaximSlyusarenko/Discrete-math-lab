#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

int n, start, m;
vector <int> term;
vector <int> from[200000][30];
bool dp[20000][200]; // перейти в состояние за n шагов
int cur_empty_number = 26;

bool check_string(string s)
{
    for (int i = 0; i < cur_empty_number; i++)
    {
        for (int j = 0; j < s.size() + 2; j++)
        {
            dp[i][j] = false;
        }
    }
    dp[0][start] = true;
    int  size = (int) s.size();
    for (int i = 1; i < size + 1; i++)
    {
        char c = s[i - 1];
        for (int j = 0; j < cur_empty_number; j++)
        {
            vector <int> fr = from[j][c - 'a'];
            bool can = false;
            for (int k = 0; k < fr.size() && !can; k++)
            {
                can |= dp[i - 1][fr[k]];
            }
            dp[i][j] = can;
        }
    }
    for (int i = 0; i < term.size(); i++)
    {
        if (dp[size][term[i]])
        {
            return true;
        }
    }
    return false;
}

int main()
{
    freopen ("automaton.in", "r", stdin);
    freopen ("automaton.out", "w", stdout);
    char c;
    cin >> n >> c;
    start = c - 'A';
    for (int i = 0; i < n; i++)
    {
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;
        int fr = s1[0] - 'A';
        char c = s3[0] - 'a';
        int to;
        if (s3.size() > 1)
        {
            to = s3[1] - 'A';
        }
        else
        {
            to = cur_empty_number;
            term.push_back(to);
            cur_empty_number++;
        }
        from[to][c].push_back(fr);
    }
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        string s;
        cin >> s;
        if (check_string(s))
        {
            cout << "yes" << endl;
        }
        else
        {
            cout << "no" << endl;
        }
    }
    return 0;
}