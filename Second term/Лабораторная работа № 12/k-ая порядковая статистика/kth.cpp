#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

int n, a[30000010], k, A, B, C;

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
	if (l < j && k <= j)
		qsort(l, j);
	if (i < r && k >= i)
		qsort(i, r);
}

int main()
{
	freopen("kth.in", "r", stdin);
	freopen("kth.out", "w", stdout);
	cin >> n >> k >> A >> B >> C >> a[0] >> a[1];
	k--;
	for (int i = 2; i < n; i++)
	{
		a[i] = A * a[i - 2] + B * a[i - 1] + C;
	}
	qsort(0, n - 1);
	cout << a[k];
	return 0;
}