#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n, k, c[110][110][110];

int main()     
{
	freopen ("num2part.in", "r", stdin);
	freopen ("num2part.out", "w", stdout);
	cin >> n >> k;
	k++;
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
	int sum = 0, i = 1, p = n;
	while (sum < p)
	{
		if (k <= c[n - i][n - i][i] || i == n)
		{
			if (sum + i == p)
				cout << i;
			else
				cout << i << "+";
			sum += i;
			n -= i;
		}
		else
		{
			k -= c[n - i][n - i][i];
			i++;
		}
	}
	return 0;
}