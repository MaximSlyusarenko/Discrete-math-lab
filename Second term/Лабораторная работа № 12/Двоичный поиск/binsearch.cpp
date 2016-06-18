#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int n, m, a[200000];

int binsearchleft(int k)
{
	int l, r;
	l = -1, r = n;
	while (r > l + 1)
	{
		int m = (l + r) / 2;
		if (a[m] >= k)
			r = m;
		else
			l = m;
	}
	if (a[r] != k)
		return -1;
	return r;
}

int binsearchright(int k)    
{
	int l, r;               
	l = -1, r = n;          
	while (r > l + 1)       
	{                       
		int m = (l + r) / 2;
		if (a[m] > k)      
			r = m;          
		else                
			l = m;          
	}
	if (a[l] != k)
		return -1;       
	return l;               
}                           

int main()
{
	freopen("binsearch.in", "r", stdin);
	freopen("binsearch.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int k;
		cin >> k;
		int l = binsearchleft(k);
		int r = binsearchright(k);
		if (l == -1 && r == -1)
		{
			cout << l << " " << r << endl;
			continue;
		}
		cout << l + 1 << " " << r + 1 << endl;
	}
	return 0;
}