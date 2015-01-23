#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int n;
double h[2000], eps = 1e-9;

int main()
{
	freopen("garland.in", "r", stdin);
	freopen("garland.out", "w", stdout);
	cin >> n >> h[0];
	double l = 0, r = h[0];
	double ans = 1000000000;
	while (r - eps > l)
	{            	
		double m = (r + l) / 2;
		h[1] = m;
		bool flag = true;
		for (int i = 2; i < n; i++)
		{
			h[i] = 2 * h[i - 1] - h[i - 2] + 2;
			if (h[i] <= eps)
				flag = false;
		}
		if (flag)
		{
			ans = min(ans, h[n - 1]);
			r = m;
		}
		else
			l = m;
	}
	printf("%0.2f", ans);
	return 0;
}