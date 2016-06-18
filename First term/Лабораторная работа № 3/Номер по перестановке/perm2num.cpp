#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n, a[30];
bool used[30];

int main()
{
	freopen ("perm2num.in", "r", stdin);
	freopen ("perm2num.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		used[i] = false;
	long long k = 0;
	for (int i = 0; i < n; i++)
	{
		long long p = 1;
		for (int j = 2; j < n - i; j++)
			p *= j;
		int r = 0;
		for (int j = 1; j < a[i]; j++)
			if (!used[j])
				r++;
		used[a[i]] = true;
		long long b = p * r;
		k += b;
	}
	cout << k;
	return 0;
}				