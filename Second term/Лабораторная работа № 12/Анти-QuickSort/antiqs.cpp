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
	freopen("antiqs.in", "r", stdin);
	freopen("antiqs.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
		a[i] = i + 1;
	for (int i = 2; i < n; i++)
	{
		int t = a[i];
		a[i] = a[i / 2];
		a[i / 2] = t;
	}
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	return 0;
}