#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

long long n, a[10010];

int main()
{
	freopen ("huffman.in", "r", stdin);
	freopen ("huffman.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	sort(a, a + n);
	int i = 0;       
	long long ans = 0;
	while (n > i + 1)
	{
		long long p = a[i] + a[i + 1];
		a[i + 1] = p;
		i++;
		ans += p;
		sort(a, a + n);
	}
	cout << ans;
	return 0;
}			