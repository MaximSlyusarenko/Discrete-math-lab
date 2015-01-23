#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

long long n, a[50][50], ans = 0;
string s;

int main()
{
	freopen ("brackets2num.in", "r", stdin);
	freopen ("brackets2num.out", "w", stdout);
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
	long long d = 0;
	for (int i = 0; i < 2 * n; i++)
		if (s[i] == '(')
			d++;
		else
		{
			ans += a[2 * n - 1 - i][d + 1];
			d--;
		}			
	cout << ans;
	return 0;
}