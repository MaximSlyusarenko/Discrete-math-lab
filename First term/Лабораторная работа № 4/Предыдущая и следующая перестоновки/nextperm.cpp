#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n, a[100010];
bool used[100010];

int main()
{
	freopen ("nextperm.in","r", stdin);
	freopen ("nextperm.out", "w", stdout); 
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		used[i] = true;
	}
	int f = -1;
	for (int i = n; i >= 1; i--)
	{
		if (!used[a[i] - 1] && a[i] > 1)
		{
			f = i;
			used[a[i]] = false;
			break;
		}
		used[a[i]] = false;
	}
	if (f == -1)
		for (int i = 1; i <= n; i++)
			cout << 0 << " ";
	else
	if (a[n - 1] > a[n])
	{
		int t = a[n - 1];
		a[n - 1] = a[n];
		a[n] = t;
		for (int i = 1; i <= n; i++)
			cout << a[i] << " ";
		t = a[n - 1];
		a[n - 1] = a[n];
		a[n] = t;
	}
	else
	{
		for (int i = 1; i <= f - 1; i++)
			cout << a[i] << " ";
		cout << a[f] - 1 << " ";
		used[a[f] - 1] = true;
		for (int i = n; i >= 1; i--)
			if (!used[i])
				cout << i << " ";
	}
	cout << endl;
	f = -1;
	for (int i = 1; i <= n; i++)
		used[i] = true;
	for (int i = n; i >= 1; i--)
	{
		if (!used[a[i] + 1] && a[i] < n)
		{
			f = i;
			used[a[i]] = false;
			break;
		}
		used[a[i]] = false;
	}
	if (f == -1)
		for (int i = 1; i <= n; i++)
			cout << 0 << " ";
	else
	if (a[n - 1] < a[n])
	{
		int t = a[n - 1];
		a[n - 1] = a[n];
		a[n] = t;
		for (int i = 1; i <= n; i++)
			cout << a[i] << " ";
	}
	else
	{
		for (int i = 1; i <= f - 1; i++)
			cout << a[i] << " ";
		cout << a[f] + 1 << " ";
		used[a[f] + 1] = true;
		for (int i = 1; i <= n; i++)
			if (!used[i])
				cout << i << " ";
	}
	return 0;
}														