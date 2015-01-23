#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

long long n, k, a[10010];

int main()
{
	freopen ("nextchoose.in", "r", stdin);
	freopen ("nextchoose.out", "w", stdout);
	cin >> n >> k;
	for (int i = 1; i <= k; i++)
		cin >> a[i];
	long long h = -1;
	for (int i = k; i >= 1; i--)
		if (a[i] < n - k + i)
		{
			a[i]++;
			h = i;
			break;
		}
	if (h == -1)
	{
		cout << -1;
		return 0;
	}
	for (int i = h + 1; i <= k; i++)
		a[i] = a[i - 1] + 1;
	for (int i = 1; i <= k; i++)
		cout << a[i] << " ";
	return 0;
}