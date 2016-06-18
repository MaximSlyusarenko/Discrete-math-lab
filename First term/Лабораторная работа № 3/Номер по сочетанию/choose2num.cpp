#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

long long n, k, a[50];

long long fact(int p)
{
	long long r = 1;
	for (int i = 2; i <= p; i++)
		r *= i;
	return r;
}

int main()
{
	freopen ("choose2num.in", "r", stdin);
	freopen ("choose2num.out", "w", stdout);
	cin >> n >> k;
	for (int i = 0; i < k ; i++)
		cin >> a[i];
	long long p = 0;
	int d = 0;
	for (int i = 0; i < k; i++)
	{
		for (int j = d + 1; j < a[i]; j++)
		{
			int q = n - j, r = k - i - 1;
			long long l = 1;
			for (int i = max(q - r, r) + 1; i <= q; i++)
				l *= i;
			l /= fact(min(q - r, r));
			p += l;
		}
		d = a[i];
	}
	cout << p;
	return 0;
}					