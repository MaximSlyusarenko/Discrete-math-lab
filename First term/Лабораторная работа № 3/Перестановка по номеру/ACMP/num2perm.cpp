#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n, k;
bool used[30];

int main()
{
	freopen ("INPUT.TXT", "r", stdin);
	freopen ("OUTPUT.TXT", "w", stdout);
	cin >> n >> k;
	k--;
	for (int i = 1; i <= n; i++)
		used[i] = false;
	for (int j = n - 1; j >= 0; j--)
	{
		long long p = 1;
		for (int i = 2; i <= j; i++)
			p *= i;
		if (k == 0)
		{
			for (int i = 1; i <= n; i++)
				if (!used[i])
					cout << i << " ";
			return 0;
		}						 
		int r = k / p;
		k -= r * p;
		r++;
		int q = 0;
		for (int i = 1; i <= n; i++)
		{
			if (!used[i])
				q++;
			if (q == r)
			{
				r = i;
				break;
			}
		}
		cout << r << " ";
		used[r] = true;
	}
	return 0;
}

