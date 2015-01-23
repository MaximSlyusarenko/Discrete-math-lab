#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <string>

using namespace std;

string s;
int a[2001][2001];

int main()
{
	freopen ("palindrome.in", "r", stdin);
	freopen ("palindrome.out", "w", stdout);
	cin >> s;
	int n = s.size();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = 0;
	for (int i = 0; i < n; i++)
		a[i][i] = 1;
	for (int i = n - 1; i >= 0; i--)
		for (int j = i + 1; j < n; j++)
		{
			int p = 0;
			if (s[i] == s[j])
				p = a[i + 1][j - 1] + 2;
			int q = a[i + 1][j], r = a[i][j - 1];
			a[i][j] = max(p, max(q, r));
		}
	cout << a[0][n - 1] << endl;
	int i = 0, j = n - 1, l = a[0][n - 1] - 1, d = 0;
	int p = 0;
	char c[2001];
	while (p < a[0][n - 1])
	{
		if (a[i][j] == a[i + 1][j - 1] + 2 && s[i] == s[j])
		{
			c[d] = s[i];
			c[l] = s[j];
			p += 2;
			i++;
			j--;
			l--;
			d++;
		}
		else
		if (i == j)
		{
			c[d] = s[i];
			p++;
		}
		else
		if (a[i][j] == a[i + 1][j])
			i++;
		else
			j--;
	}
	for (int k = 0; k < a[0][n - 1]; k++)
		cout << c[k];			
	return 0;
}