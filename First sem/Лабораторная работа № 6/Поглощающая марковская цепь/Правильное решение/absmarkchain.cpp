
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
 
using namespace std;
 
int n, m, a[200000], b[200000], kola = 0, pos[500];
double p[200000], q[500][1000], f[500][500], r[500][500], obr[500][500];
bool flag[500];
 
int main()
{
    freopen ("absmarkchain.in", "r", stdin);
    freopen ("absmarkchain.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        flag[i] = false;
    for (int i = 1; i <= m; i++)
    {
        cin >> a[i] >> b[i] >> p[i];
        if (a[i] == b[i] && p[i] == 1)
        {
            flag[a[i]] = true;
            kola++;
        }
    }
    int z = 0, l = 0;
    for (int i = 1; i <= n; i++)
        if (!flag[i])
        {
            z++;
            pos[i] = z;
        }
        else
        {
            l++;
            pos[i] = l;
        }
    for (int i = 1; i <= m; i++)
    {
        if (flag[b[i]])
        {
            if (!flag[a[i]])
                r[pos[a[i]]][pos[b[i]]] = p[i];
        }
        else
            q[pos[a[i]]][pos[b[i]]] = p[i];
    }   
    int d = n - kola;
    for (int i = 1; i <= d; i++)
        for (int j = 1; j <= d; j++)
        {
            if (i == j)
                q[i][j] = 1 - q[i][j];
            else
                q[i][j] = -q[i][j];
        }
    for (int i = 1; i <= d; i++)
        for (int j = d + 1; j <= 2 * d; j++)
            if (j - d == i)
                q[i][j] = 1;
            else
                q[i][j] = 0;
    for (int i = 1; i <= d; i++)
    {
        double c = q[i][i];
        if (c != 1)
            for (int j = 1; j <= 2 * d; j++)
                q[i][j] = q[i][j] / c;
        for (int j = i + 1; j <= d; j++)
        {
            c = q[j][i];
            for (int k = 1; k <= 2 * d; k++)
                q[j][k] = q[j][k] - c * q[i][k];
        }
    }
    for (int i = d; i >= 1; i--)
    {
        for (int j = i - 1; j >= 1; j--)
        {
            double v = q[j][i];
            for (int k = 1; k <= 2 * d; k++)
                q[j][k] = q[j][k] - v * q[i][k];
        }
    }
    for (int i = 1; i <= d; i++)
        for (int j = d + 1; j <= 2 * d; j++)
            obr[i][j - d] = q[i][j];    
    for (int i = 1; i <= d; i++)
    {
        double sum = 0;
        for (int j = 1; j <= kola; j++)
        {
            sum = 0;
            for (int k = 1; k <= d; k++)
                sum = sum + obr[i][k] * r[k][j];
            f[i][j] = sum;
        }
    }   
    for (int i = 1; i <= n; i++)
        if (!flag[i])
            cout << "0.0" << endl;
        else
        {
            double ans = 0;
            for (int j = 1; j <= d; j++)
                ans = ans + f[j][pos[i]];
            ans = ans + 1;
            double an = ans / double(n);
            cout.precision(10);
            cout << an << endl;
        }                                                           
    return 0;
}