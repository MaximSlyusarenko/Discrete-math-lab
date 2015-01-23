#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int n, a[10000], d[10000];
vector <int> b;

int main()
{
	freopen ("lis.in", "r", stdin);
	freopen ("lis.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n; i++)
	{
		d[i] = 1;
		for (int j = 0; j < i; j++)
			if (a[j] < a[i] && d[j] + 1 > d[i])
				d[i] = d[j] + 1;
	}
	int maxi = -1, c;
	for (int i = 0; i < n; i++)
		if (d[i] > maxi)
		{
			maxi = d[i];
			c = i;
		}
	cout << maxi << endl;
	b.push_back(a[c]);
	while (d[c] > 1)
	{
		int t;
		for (int i = 0; i < c; i++)
			if (d[i] + 1 == d[c] && a[i] < a[c])
			{
				t = i;
				break;
			}
		b.push_back(a[t]);
		c = t;
	}
	reverse(b.begin(), b.end());
	for (int i = 0; i < b.size(); i++)
		cout << b[i] << " ";			
	return 0;
}				