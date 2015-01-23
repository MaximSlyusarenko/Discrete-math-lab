#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
 
using namespace std;
 
long long a[1001][10001], w[1001], p[1001], n, m;
vector <long long> ans;          
 
int main()
{
    freopen ("knapsack.in", "r", stdin);
    freopen ("knapsack.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 1; i <= n; i++)
        cin >> p[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            a[i][j] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            a[i][j] = a[i - 1][j];
            if (j >= w[i])
                if (a[i - 1][j - w[i]] + p[i] > a[i][j])
                    a[i][j] = a[i - 1][j - w[i]] + p[i];
        }
    long long i = n, j = m;
    long long cost = a[n][m], c = 0;
    while (c < cost)
    {
    	if (a[i - 1][j] == a[i][j])
    		i--;
    	else
    	{
    		ans.push_back(i);
    		j -= w[i];
    		c += p[i];
    		i--;
    	}
    }
    cout << ans.size() << endl;
    long long r = ans.size();
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < r; i++)
        cout << ans[i] << " ";     
    return 0;
}  