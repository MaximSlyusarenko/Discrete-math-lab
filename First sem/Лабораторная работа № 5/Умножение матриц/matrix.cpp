#include <iostream>
#include <cmath>
#include<algorithm>
#include <cstdio>

using namespace std;

long long n, a[500], b[500], d[500][500], st[500][500];
bool used[500];

string print(int i, int j)
{
	//cerr << i << " " << j << endl;
	if (i == j)
		return "A";
	return "(" + print (i, st[i][j]) + print (st[i][j] + 1, j) + ")";
}                                              

int main()
{
	freopen ("matrix.in", "r", stdin);
	freopen ("matrix.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i] >> b[i];
	long long inf = 1000000000;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			d[i][j] = inf;
	for (int i = 1; i <= n; i++)
		d[i][i] = 0;
	for (int i = n; i >= 1; i--)
		for (int j = i + 1; j <= n; j++)
		{
			for (int k = i; k < j; k++)
			{
				int cur = d[i][k] + d[k + 1][j] + a[i] * b[k] * b[j];
				if (cur < d[i][j])
				{
					d[i][j] = cur;
					st[i][j] = k;
				}
			}
		}
	string s = print(1, n);
	cout << s;
	return 0;
}