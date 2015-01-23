
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <fstream>
#include <stdexcept>
  
using namespace std;
  
int n, x[10000], y[10000], cost[10000];
double ans = 0.0;
set <pair <int, int> > s;
bool used[10000];
  
int main()
{
    ifstream in("spantree.in");
    ofstream out("spantree.out");
    in >> n;    
    for (int i = 0; i < n; i++)
    {
        in >> x[i] >> y[i];
        cost[i] = 2000000000;
        used[i] = false;
    }
    cost[0] = 0;
    for (int i = 0; i < n; i++)
    {
        int v = -1;
        for (int j = 0; j < n; j++)
        {
            if (!used[j] && (v == -1 || cost[j] < cost[v]))
            {
                v = j;
            }
        }
        used[v] = true;
        for (int j = 0; j < n; j++)
        {
            int tmp = (x[v] - x[j]) * (x[v] - x[j]) + (y[v] - y[j]) * (y[v] - y[j]);
            if (!used[j] && tmp < cost[j])
            {
                cost[j] = tmp;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        ans += double(sqrt(double(cost[i])));
    }
    out.precision(10);
    out << ans;                                                           
    return 0;
}