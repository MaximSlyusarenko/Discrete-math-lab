#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

int n, m, p[200000], rang[200000];
long long s;
vector <pair <pair <long long, int>, pair <int, int> > > g;
vector <long long> number_to_weight;
long long sum = 0;
long long input_sum = 0;
vector <bool> was_edge;
vector <pair <long long, int> > was_not_in_edge;
vector <int> ans;

int get(int v)
{
    while (v != p[v])
    {
        v = p[v];
    }
    return v;
}

void unio(int k, int q)
{
    k = get(k);
    q = get(q);
    if (k != q)
    {
        if (rang[k] == rang[q])
        {
            rang[k]++;
            p[q] = k;
        }
        else if (rang[k] < rang[q])
        {
            p[k] = q;
        }
        else
        {
            p[q] = k;
        }
    }
}

int main()
{
    freopen ("destroy.in", "r", stdin);
    freopen ("destroy.out", "w", stdout);
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        input_sum += c;
        g.push_back(make_pair(make_pair(c, i), make_pair(a, b)));
        was_edge.push_back(false);
        number_to_weight.push_back(c);
    }
    sort(g.begin(), g.end());
    reverse(g.begin(), g.end());
    for (int i = 1; i <= n; i++)
    {
        p[i] = i;
        rang[i] = 1;
    }
    for (int i = 0; i < m; i++)
    {
        if (get(g[i].second.first) != get(g[i].second.second))
        {
            sum += g[i].first.first;
            was_edge[g[i].first.second] = true;
            unio(g[i].second.first, g[i].second.second);
        }
    }
    for (int i = 0; i < m; i++)
    {
        if (!was_edge[i])
        {
            was_not_in_edge.push_back(make_pair(number_to_weight[i], i));
        }
    }
    sort(was_not_in_edge.begin(), was_not_in_edge.end());
    reverse(was_not_in_edge.begin(), was_not_in_edge.end());
    int i = 0;
    while (i < was_not_in_edge.size() && input_sum - sum > s)
    {
        sum += was_not_in_edge[i].first;
        was_edge[was_not_in_edge[i].second] = true;
        i++;
    }
    for (int j = 0; j < m; j++)
    {
        if (!was_edge[j])
        {
            ans.push_back(j + 1);
        }
    }
    cout << ans.size() << endl;
    for (int j = 0; j < ans.size(); j++)
    {
        cout << ans[j] << " ";
    }
    return 0;
}