#include <iostream>
#include <cmath>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <iomanip>

using namespace std;

long long a[1000001], t[4000001], n, m;
	
void sozd(long long v, long long l, long long r)
{
	if (l == r)
	{
		t[v] = a[l];
	}
	else
	{
		long long k = (l + r) / 2;
		sozd(2 * v, l, k);
		sozd(2 * v + 1, k + 1, r);
		t[v] = t[2 * v] + t[2 * v + 1];
	}
}

long long searchsum(long long v, long long lk, long long rk, long long l, long long r)
{
	long long d;
	if (l > r)
	{
		return 0;
	}
	if (lk == l && rk == r)
	{
		d = t[v];
		return d;
	}
	long long k = (lk + rk) / 2;
	long long b, c;
	b = searchsum(2 * v, lk, k, l, min(k, r));
	c = searchsum(2 * v + 1, k + 1, rk, max(k + 1, l), r);
	d = b + c;
	return d;
}

int main()
{
	std::ios_base::sync_with_stdio(0);
	freopen ("rsq.in", "r", stdin);
	freopen ("rsq.out", "w", stdout);
	long long d;
	long long l, r;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	sozd(1, 1, n);
	string s;
	while (cin >> s >> l >> r)
	{
		if (s == "sum")
		{
			d = searchsum(1, 1, n, l, r);
			cout << d << endl;
		}
		if (s == "set")
		{
			long long left = 1, right = n, v = 1;               	
			while (left < right)                          
			{                                      
				long long k = (left + right) / 2;               
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
				t[v] = t[2 * v] + t[2 * v + 1];
				v /= 2;                            
			}		                               
		}
	}
	return 0;
}