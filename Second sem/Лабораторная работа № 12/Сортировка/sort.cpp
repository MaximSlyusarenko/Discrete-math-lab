#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

int n, a[200000];

void qsort(int l, int r)
{
	srand((double)time(NULL));
	int m = l + (rand() % (r - l));
	int x = a[m];
	int i = l, j = r;
	while (i <= j)
	{
		while (a[i] < x  && i <= r)
			i++;
		while (a[j] > x && j >= l)
			j--;
		if (i <= j)
		{
			int t = a[i];
			a[i] = a[j];
			a[j] = t;
			i++;
			j--;
		}
	}
	if (l < j)
		qsort(l, j);
	if (i < r)
		qsort(i, r);
}

int main()
{
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	qsort(0, n - 1);
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	return 0;
}