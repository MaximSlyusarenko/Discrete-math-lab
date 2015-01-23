#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int n, r[100], a[100][100][5];

int main()
{
	freopen("netbuild.in", "r", stdin);
	freopen("netbuild.out", "w", stdout);
	cin >> n;
	cout << n << " ";
	int comparators = 0;
	int s = 0;
	for (int i = 0; i < n; i += 2)
	{
		a[s][r[0]][1] = i;
		a[s][r[0]][2] = i + 1;
		comparators++;
		r[0]++;
	}
	s++;
	for (int i = 2; i <= n; i *= 2)
	{   	
		for (int k = i; k >= 1; k /= 2)
		{
			int h = k;
			if (k == 1)
				h = 2;
			for (int j = 0; j < n / i; j++)
			{
				if (k + j < n)
				{
					a[s][r[s]][1] = j;
					a[s][r[s]][2] = j * ;	
					comparators++;
					r[s]++;
				}
			}
			if (r[s] != 0)
				s++;
		}
	}
	cout << s << " " << comparators << endl;
	for (int i = 0; i < s; i++)
	{
		cout << r[i] << " ";
		for (int j = 0; j < r[i]; j++)
			cout << a[i][j][1] + 1 << " " << a[i][j][2] + 1 << " ";
		cout << endl;
	}
	return 0;
}