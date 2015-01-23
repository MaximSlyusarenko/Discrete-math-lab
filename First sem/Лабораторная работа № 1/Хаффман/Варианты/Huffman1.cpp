#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int n, p, a[1010];
queue <long long> q;

int main()
{
	freopen ("huffman.in", "r", stdin);
	freopen ("huffman.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	sort(a, a + n);
	long long ans = 0;
	int i = 0;
	while (i < n || q.size() > 1)
	{
		if (i < n - 1 && (q.empty() || (a[i] <= q.front() && a[i + 1] <= q.front())))
		{
			p = a[i] + a[i + 1];
			ans += p;
			q.push(p);
			i += 2;
		}
		else
		{
			int d = q.front();
			q.pop();
			if (i < n && ((a[i] <= d && a[i + 1] > d) || (i == n - 1 && a[i] <= q.front()) || q.empty()))
			{
				p = a[i] + d;
				ans += p;
				q.push(p);
				i++;
			}
			else
			{
				int r = q.front();
				p = d + r;
				q.pop();
				q.push(p);
				ans += p;
			}
		}
	}
	cout << ans;
	return 0;
}                     