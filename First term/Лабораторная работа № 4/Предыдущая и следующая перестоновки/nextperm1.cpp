#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int a[100010], n;
bool used[100010];

int main()
{
	freopen ("nextperm.in", "r", stdin);
	freopen ("nextperm.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		used[i] = false;
	int h = -1;
	for (int i = n; i > 1; i--)
		if (a[i] < a[i - 1])
		{
			h = i;
			break;
		}

	if (h == -1)
	{
		for (int i = 1; i <= n; i++)
			cout << 0 << " ";
	}
	else
	{
		int q = a[h - 1], maxi = -1;
		for (int i = h; i <= n; i++)
			if (a[i] > maxi && a[i] < q)
				maxi = a[i];
		for (int i = 1; i < h - 1; i++)
			used[a[i]] = true;
		used[maxi] = true;
		for (int i = 1; i < h - 1; i++)
			cout << a[i] << " ";
		cout << maxi << " ";
		for (int i = n; i >= 1; i--)
			if (!used[i])
				cout << i << " ";
	}
	cout << endl;
	for (int i = 1; i <= n; i++)
		used[i] = false;
	h = -1;   // следующая
	for (int i = n; i > 1; i--)
		if (a[i] > a[i - 1])
		{
			h = i;
			break;
		}
	if (h == -1)
	{
		for (int i = 1; i <= n; i++)
			cout << 0 << " ";
		return 0;
	}
	int q = a[h - 1], mini = 100010;
	for (int i = h; i <= n; i++)
		if (a[i] < mini && a[i] > q)
			mini = a[i];
	for (int i = 1; i < h - 1; i++)
		used[a[i]] = true;
	a[h - 1] = mini;
	used[mini] = true;
	for (int i = 1; i <= h - 1; i++)
		cout << a[i] << " ";
	for (int i = 1; i <= n; i++)
		if (!used[i])
			cout << i << " ";
	return 0;
}							 				