#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n, k, a[20];
bool used[20];

void gen(int pos)
{
	if (pos == k)
	{
		for (int i = 0; i < k; i++)
			cout << a[i] << " ";
		cout << endl;
		return;
	}
	for (int i = 1; i <= n; i++)
		if (!used[i] && i > a[pos - 1])
		{
			a[pos] = i;
			used[i] = true;
			gen(pos + 1);
			used[i] = false;
		}
}

int main()
{
	freopen ("choose.in", "r", stdin);
	freopen ("choose.out", "w", stdout);
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		used[i] = false;
	gen(0);
	return 0;
}