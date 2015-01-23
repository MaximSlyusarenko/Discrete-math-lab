#include <iostream>
#include <cmath>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <vector>

using namespace std;

int a[200000], t[400001], n, m, inf = 1000000000;
bool flag[200000];
	
void sozd(int v, int l, int r)
{
	if (l == r)
	{
		if (flag[l])
			t[v] = a[l];
		else
			t[v] = -inf;
	}
	else
	{
		int k = (l + r) / 2;
		sozd(2 * v, l, k);
		sozd(2 * v + 1, k + 1, r);
		if (t[2 * v + 1] > t[2 * v])
		{
			t[v] = t[2 * v + 1];	
		}
		else
		{
			t[v] = t[2 * v];
		}
	}
}

int searchmax(int v, int val, int l, int r)
{
	if (l == r)
	{
		flag[l] = false;
		t[v] = -inf;
		v /= 2;
		while (v >= 1)
		{
			t[v] = max(t[2 * v], t[2 * v + 1]);
			v /= 2;
		}		
		return a[l];
	}
	else
	if (t[2 * v] >= val)
	{
		return searchmax(2 * v, val, l, (l + r) / 2);
	}
	else
	if (t[2 * v + 1] >= val)
	{
		return searchmax(2 * v + 1, val, (l + r) / 2 + 1, r);
	}		
	else
	{
		return searchmax(1, 1, 1, n);
	}
}

int main()
{
	freopen ("parking.in", "r", stdin);
	freopen ("parking.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		a[i] = i;
		flag[i] = true;
	}
	sozd(1, 1, n);
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		string s;
		int q;
		cin >> s >> q;
		if (s == "enter")
		{
			int d;
			d = searchmax(1, q, 1, n);
			cout << d << endl;
		}
		else
		{
			flag[q] = true;
			int l = 1, r = n, v = 1;
			while (l < r)
			{
				int k = (l + r) / 2;
				if (k >= q)
				{
					r = k;
					v *= 2;
				}
				else
				{
					l = k + 1;
					v = 2 * v + 1;
				}
			}
			t[v] = a[l];                              
			v /= 2;                                   
			while (v >= 1)                            
			{                                         
				t[v] = max(t[2 * v], t[2 * v + 1]);   
				v /= 2;                               
			}		                                  
		}
	}
	return 0;
}