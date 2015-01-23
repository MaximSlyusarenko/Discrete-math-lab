#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

long long n, a[50][50], c[100], ans = 0, b[100], k;

long long st(long long a, long long b)
{
	long long t = 1;
	for (int i = 1; i <= b; i++)
		t *= a;
	return t;
}

int main()
{
	freopen ("num2brackets2.in", "r", stdin);
	freopen ("num2brackets2.out", "w", stdout);
	cin >> n >> k;
	for (int i = 0; i <= 2 * n; i++)
		for (int j = 0; j <= n; j++)
			a[i][j] = 0;
	a[0][0] = 1;
	for (int i = 0; i < 2 * n; i++)
		for (int j = 0; j <= n; j++)
		{
			if (j < n)
				a[i + 1][j + 1] += a[i][j];	
			if (j > 0)
				a[i + 1][j - 1] += a[i][j];
		}
	long long d = 0, r = 0, h = 0;
	string ans = "";
	for (int i = 2 * n - 1; i >= 0; i--)
	{
		long long cur;
		if (d < n)
			cur = a[i][d + 1] * st(2, (i - d - 1) / 2);
		else
			cur = 0;
		if (cur > k)
		{
			ans += '(';
			d++;
			b[h] = r;
			h++;
			r = 0;
			continue;
		}
		k -= cur;
		if (d > 0 && r == 0)
			cur = a[i][d - 1] * st(2, (i - d + 1) / 2);
		else
			cur = 0;
		if (cur > k)
		{
			ans += ')';
			d--;
			r = b[h - 1];
			h--;
			continue;
		}
		if (cur <= k)
			k -= cur;
		if (d < n)
			cur = a[i][d + 1] * st(2, (i - d - 1) / 2);
		else
			cur = 0;
		if (cur > k)
		{
			ans += '[';
			d++;
			r++;
			continue;
		}
		k -= cur;
		ans += ']';
		d--;
		r--;
	}
	cout << ans;
	return 0;
}