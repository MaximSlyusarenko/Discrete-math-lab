
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
 
using namespace std;
 
int n, a[500][500], p[500], minv[500], used[500], u[500], v[500], ans[500], w[500];
const int inf = 2000000000;
 
int main()
{
    freopen ("assignment.in", "r", stdin);
    freopen ("assignment.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        p[0] = i;
        int j0 = 0;
        for (int j = 0; j <= n + 1; j++)
        {
            minv[j] = inf;
        }
        for (int j = 0; j <= n + 1; j++)
        {
            used[j] = false;
        }
        bool first_time_here = true;
        while (p[j0] != 0 || first_time_here)
        {
            used[j0] = true;
            int curi = p[j0];
            int delta = inf;
            int curj;
            for (int j = 1; j <= n; j++)
            {
                if (!used[j])
                {
                    int cur = a[curi][j] - u[curi] - v[j];
                    if (cur < minv[j])
                    {
                        minv[j] = cur;
                        w[j] = j0;
                    }
                    minv[j] = min(cur, minv[j]);
                    if (delta > minv[j])
                    {
                        delta = minv[j];
                        curj = j;
                    }
                }
            }
            for (int j = 0; j <= n; j++)
            {
                if (used[j])
                {
                    u[p[j]] += delta;
                    v[j] -= delta;
                }
                else
                {
                    minv[j] -= delta;
                }
            }
            j0 = curj;
            first_time_here = false;
        }
        while (j0 != 0)
        {
            int cur = w[j0];
            p[j0] = p[cur];
            j0 = cur;
        }
    }
    cout << -v[0] << endl;
    for (int i = 1; i <= n; i++)
    {
        ans[p[i]] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        cout << i << " " << ans[i] << endl;
    }
    return 0;
}