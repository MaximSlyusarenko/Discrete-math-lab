#include <iostream>
#include <cmath>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <iomanip>

using namespace std;

int a[1000001], t[4000001], n, m;
	
void sozd(int v, int l, int r)
{
	if (l == r)
	{
		t[v] = a[l];
	}
	else
	{
		int k = (l + r) / 2;
		sozd(2 * v, l, k);
		sozd(2 * v + 1, k + 1, r);
		if (t[2 * v + 1] < t[2 * v])
		{
			t[v] = t[2 * v + 1];	
		}
		else
		{
			t[v] = t[2 * v];
		}
	}
}

int searchmin(int v, int lk, int rk, int l, int r)
{
	int d;
	if (l > r)
	{
		d = 1000000001;
		return d;
	}
	if (lk == l && rk == r)
	{
		d = t[v];
		return d;
	}
	int k = (lk + rk) / 2;
	int b, c;
	b = searchmin(2 * v, lk, k, l, min(k, r));
	c = searchmin(2 * v + 1, k + 1, rk, max(k + 1, l), r);
	d = min(b, c);
	return d;
}

int main()
{
	std::ios_base::sync_with_stdio(0);
	freopen ("rmq.in", "r", stdin);
	freopen ("rmq.out", "w", stdout);
	int d;
	int l, r;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	sozd(1, 1, n);
	string s;
	while (cin >> s >> l >> r)
	{
		if (s == "min")
		{
			d = searchmin(1, 1, n, l, r);
			cout << d << endl;
		}
		if (s == "set")
		{
			int left = 1, right = n, v = 1;               	
			while (left < right)                          
			{                                      
				int k = (left + right) / 2;               
				if (k >= l)                        
				{                                  
					right = k;                         
					v *= 2;                        
				}                                  
				else                               
				{                                  
					left = k + 1;                     
					v = 2 * v + 1;                 
				}                                  
			}                                      
			t[v] = r;                           
			v /= 2;                                
			while (v >= 1)                         
			{                                      
				t[v] = min(t[2 * v], t[2 * v + 1]);
				v /= 2;                            
			}		                               
		}
	}
	return 0;
}