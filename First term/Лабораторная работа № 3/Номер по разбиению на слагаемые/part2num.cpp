#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n, k, c[110][110][110], a[110];
char f;

int main()     
{
	freopen ("part2num.in", "r", stdin);
	freopen ("part2num.out", "w", stdout);
	int r = 0, n = 0;
	while (cin >> a[r])
	{
		cin >> f;
		n += a[r];
		r++;
	}
	r--;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			for (int k = 1; k <= n; k++)
				c[i][j][k] = 0;
	for (int i = 1; i <= n; i++)
		for (int k = 1; k <= i; k++)
			c[0][i][k] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= j; k++)
				if (i >= j)
					c[i][j][k] = c[i][j - 1][k] + c[i - j][j][k]; //Разбиение числа i на слагаемые, не превосходящие j и не меньшие k
				else
				if (i >= k)
					c[i][j][k] = c[i][i][k];
	int num = 0, prev = 1;
	for (int i = 0; i <= r; i++)
	{
		for (int j = prev; j < a[i]; j++)
			num += c[n - j][n - j][j];
		prev = a[i];
		n -= a[i];
	}
	cout << num;
	return 0;
}