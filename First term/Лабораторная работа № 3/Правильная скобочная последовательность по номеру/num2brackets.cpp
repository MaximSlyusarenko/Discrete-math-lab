#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

long long n, k, a[50][50];
string s = "";

int main()
{
	freopen ("num2brackets.in", "r", stdin);
	freopen ("num2brackets.out", "w", stdout);
	cin >> n >> k;
	k++;
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
	for (int i = 2 * n - 1; i >= 0; i--)
		if (d < n && a[i][d + 1] >= k)
		{
			s += "(";
			d++;
		}
		else
		{
			s += ")";
			if (d < n)
				k -= a[i][d + 1];
			d--;
		}
	cout << s;
	return 0;
}