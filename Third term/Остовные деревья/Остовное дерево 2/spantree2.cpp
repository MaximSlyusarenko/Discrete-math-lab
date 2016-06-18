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

long long n, m, a, b, c, p[50000], rang[50000], ans = 0;
pair <int, pair <int, int> > g[200000];

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
	freopen ("spantree2.in", "r", stdin);
	freopen ("spantree2.out", "w", stdout);
	cin >> n >> m;	
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> c;
		g[i].first = c;
		g[i].second.first = a;
		g[i].second.second = b;
	}
	sort(g, g + m);
	for (int i = 1; i <= n; i++)
	{
		p[i] = i;
		rang[i] = 1;
	}
	for (int i = 0; i < m; i++)
	{
		if (get(g[i].second.first) != get(g[i].second.second))
		{
			ans += g[i].first;
			unio(g[i].second.first, g[i].second.second);
		}
	}
	cout << ans;
	return 0;
}