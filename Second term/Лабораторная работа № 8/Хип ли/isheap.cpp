#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int n, a[200000];

int main()
{
	freopen ("isheap.in", "r", stdin);
	freopen ("isheap.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
	{
		if (2 * i <= n)
			if (a[i] > a[2 * i])
			{
				cout << "NO";
				return 0;
			}
		if (2 * i + 1 <= n)
			if (a[i] > a[2 * i + 1])
			{
				cout << "NO";
				return 0;
			}
	}
	cout << "YES";
	return 0;
}