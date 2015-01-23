#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

long long fact(int k)
{
	long long p = 1;
	for (int i = 2; i <= k; i++)
		p *= i;
	return p;
}

long long n, k, m;

int main()
{
	freopen ("num2choose.in", "r", stdin);
	freopen ("num2choose.out", "w", stdout);
	cin >> n >> k >> m;
	int f = 0;
	for (int i = 0; i < k; i++)       	
		for (int j = f + 1; j <= n; j++)
		{
			int p = n - j, q = k - i - 1;
			long long l = 1;
			for (int i = max(p - q, q) + 1; i <= p; i++)
				l *= i;
			l /= fact(min(p - q, q));
			if (m == 0)
			{
				int h = j;
				for (int s = i; s < k; s++)
				{
					cout << h << " ";
					h++;
				}
				return 0;
			}
			if (m >= l)
				m -= l;
			else
			{
				f = j;
				cout << j << " ";
				break;
			}
		}
	return 0;
}