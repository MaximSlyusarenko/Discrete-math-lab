#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>

using namespace std;

int n;
double a[200][200], m[200][200], q[200][200], b[200], ans[200];

int main()
{
	freopen ("markchain.in", "r", stdin);
	freopen ("markchain.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			cin >> a[i][j];
			m[i][j] = a[i][j];
		}
	for (int i = 1; i <= n; i++)
		b[i] = 1 / double(n);
	for (int i = 1; i <= 50; i++)
	{
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= n; k++)
			{
				double sum = 0;
				for (int p = 1; p <= n; p++)
					sum += a[j][p] * m[p][k];
				q[j][k] = sum;
			}
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= n; k++)
				a[j][k] = q[j][k];
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			ans[i] += b[j] * a[j][i];
	for (int i = 1; i <= n; i++)
		cout << ans[i] << endl;
	return 0;
}										