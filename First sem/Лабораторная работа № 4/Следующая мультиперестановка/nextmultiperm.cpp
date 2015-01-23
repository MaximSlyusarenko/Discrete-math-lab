#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n, a[100010];

int main()
{
	freopen ("nextmultiperm.in", "r", stdin);
	freopen ("nextmultiperm.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	int h = -1;
	for (int i = n - 1; i > 0; i--)
		if (a[i] > a[i - 1])
		{
			h = i - 1;
			break;
		}
	if (h == -1)
	{
		for (int i = 0; i < n; i++)
			cout << 0 << " ";
		return 0;
	}
	int r, mini = 100010;
	for (int i = h + 1; i < n; i++)
		if (a[i] < mini && a[i] > a[h])
			r = i;
	int t = a[h];
	a[h] = a[r];
	a[r] = t;
	sort(a + h + 1, a + n);
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	return 0;
}