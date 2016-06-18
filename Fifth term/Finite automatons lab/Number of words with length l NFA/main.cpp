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
long long dp[2000][20000]; // dp[i][j] - сколько слов длины i можно получить, придя в состояние j
vector <int> to[200000][30];
bool is_term[200];

int Thompson()
{
    queue <pair <vector <int>, int> > p;
    vector <int> start;
    start.push_back(1);
    p.push(make_pair(start, 1));
    map <vector <int>, int> qd;
    qd.insert(make_pair(start, 1));
    int cur_number = 1;
    if (is_term[1])
    {
        term.push_back(1);
    }
    while (p.size() > 0)
    {
        vector <int> cur = p.front().first;
        int current_number = p.front().second;
        p.pop();
        /*cerr << "cur" << endl;
        for (int i = 0; i < (int) cur.size(); i++)
        {
            cerr << cur[i] << " ";
        }
        cerr << endl;*/
        for (int i = 0; i <= symbols; i++)
        {
            vector <int> qcur;
            bool also_in_qcur[2000] = {};
            bool ter = false;
            for (int j = 0; j < (int) cur.size(); j++)
            {
                //cerr << cur[j] << " " << i + 'a' << " " << to[cur[j]][i].size() << endl;
                for (int k = 0; k < (int) to[cur[j]][i].size(); k++)
                {
                    if (is_term[to[cur[j]][i][k]])
                    {
                        ter = true;
                    }
                    if (!also_in_qcur[to[cur[j]][i][k]])
                    {
                        qcur.push_back(to[cur[j]][i][k]);
                        also_in_qcur[to[cur[j]][i][k]] = true;
                    }
                }
            }
            if (qcur.size() == 0)
            {
                continue;
            }
            /*cerr << "qcur" << endl;
            for (int j = 0; j < (int) qcur.size(); j++)
            {
                cerr << qcur[j] << " ";
            }
            cerr << endl;*/
            /*bool is_end = true;
            int number = -1;
            for (int q = 1; q <= cur_number; q++)
            {
                if (qd.find(make_pair(qcur, q)) != qd.end())
                {
                    is_end = false;
                    number = q;
                }
            }*/
            if (qd.find(qcur) == qd.end())
            {
                p.push(make_pair(qcur, cur_number + 1));
                qd.insert(make_pair(qcur, cur_number + 1));
                from[cur_number + 1][i].push_back(current_number);
                if (ter)
                {
                    term.push_back(cur_number + 1);
                }
                cur_number++;
            }
            else
            {
                from[qd.find(qcur) -> second][i].push_back(current_number);
            }
        }
    }
    return cur_number;
}

int main()
{
    freopen ("problem5.in", "r", stdin);
    freopen ("problem5.out", "w", stdout);
    int n, m, k, l = 0;
    cin >> n >> m >> k >> l;
    for (int i = 0; i < k; i++)
    {
        int tmp = 0;
        cin >> tmp;
        is_term[tmp] = true;
    }
    for (int i = 0; i < m; i++)
    {
        int from, t;
        char c;
        cin >> from >> t >> c;
        to[from][c - 'a'].push_back(t);
    }
    n = Thompson();
    /*cerr << n << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= symbols; j++)
        {
            vector <int> fr = from[i + 1][j];
            for (int q = 0; q < (int) fr.size(); q++)
            {
                cerr << fr[q] << " " << i + 1 << " " << j << endl;
            }
        }
    }*/
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