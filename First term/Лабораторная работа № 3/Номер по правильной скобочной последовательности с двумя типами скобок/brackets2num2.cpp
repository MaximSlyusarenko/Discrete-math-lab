#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

long long n, a[50][50], c[100], ans = 0;
string s;

long long st(long long a, long long b)
{
	long long t = 1;
	for (int i = 1; i <= b; i++)
		t *= a;
	return t;
}

int main()
{
	freopen ("brackets2num2.in", "r", stdin);
	freopen ("brackets2num2.out", "w", stdout);
	cin >> s;
	n = s.size() / 2;
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
	long long d = 0, k, q = 0, r = 0;
	for (int i = 0; i < 2 * n; i++)
		if (s[i] == '(')
		{
			d++;
			c[r] = q;
			r++;
			q = 0;
		}
		else
		if (s[i] == ')')
		{
			k = d + 1;
			if (k <= n)
				ans += a[2 * n - i - 1][k] * st(2, (2 * n - i - k - 1) / 2);
			d--;
			q = c[r - 1];
			r--;
		}
		else
		if (s[i] == '[')
		{
			if (q == 0)
			{
				k = d - 1;
				if (k >= 0)     
					ans += a[2 * n - i - 1][k] * st(2, (2 * n - i - k - 1) / 2);
			}
			k = d + 1;
			ans += a[2 * n - i - 1][k] * st(2, (2 * n - i - k - 1) / 2);
			d++;
			q++;
		}
		else
		{
			k = d + 1;
			if (k <= n)
				ans += 2 * a[2 * n - i - 1][k] * st(2, (2 * n - i - k - 1) / 2);
			d--;
			q--;
		}			
	cout << ans;
	return 0;
}