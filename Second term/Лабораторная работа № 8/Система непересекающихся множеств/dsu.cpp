#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int n, p[200000], mini[200000], maxi[200000], kol[200000], r[200000]; 

int main()
{
	freopen ("dsu.in", "r", stdin);
	freopen ("dsu.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		p[i] = i;
		mini[i] = i;
		maxi[i] = i;
		kol[i] = 1;
		r[i] = 1;
	}
	string s;
	while (cin >> s)
	{
		if (s == "union")
		{
			int k, q;
			cin >> k >> q;
			while (p[k] != k)
			{
				k = p[k];
			}
			while (p[q] != q)
			{
				q = p[q];
			}
			if (k != q)
			{
				if (r[k] == r[q])
				{
					r[k]++;
					p[q] = k;
					if (mini[q] < mini[k])
						mini[k] = mini[q];
					if (maxi[q] > maxi[k])
						maxi[k] = maxi[q];
					kol[k] += kol[q];			
				}
				else if (r[k] < r[q])
				{
					p[k] = q;
					if (mini[k] < mini[q])  
						mini[q] = mini[k];  
					if (maxi[k] > maxi[q])  
						maxi[q] = maxi[k];  
					kol[q] += kol[k];		
				}
				else
				{
					p[q] = k;
					if (mini[q] < mini[k])  
						mini[k] = mini[q];  
					if (maxi[q] > maxi[k])  
						maxi[k] = maxi[q];  
					kol[k] += kol[q];		
				}
			}
		}
		else
		{
			int k;
			cin >> k;
			while (p[k] != k)
				k = p[k];
			cout << mini[k] << " " << maxi[k] << " " << kol[k] << endl;
		}
	}
	return 0;
}