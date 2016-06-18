#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n, a[1001], b[2001], len[1001], q;
vector <int> c[2001];

int main()
{
	freopen ("huffman.in", "r", stdin);
	freopen ("huffman.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < 2001; i++)
		b[i] = 0;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	sort(a, a + n);
	int i = 0;
	int start = 0, finish = 0;
	while ((i < n && start <= finish) || (b[start + 1] != 0 && i == n))
	{
		if ((start == finish || (a[i] <= b[start] && a[i + 1] <= b[start])) && i + 1 < n)
		{
			b[finish] = a[i] + a[i + 1];
			c[finish].push_back(i);
			c[finish].push_back(i + 1);
			len[i]++;
			len[i + 1]++;
			i += 2;
			finish++;
		}
		else if (((a[i] <= b[start] && a[i + 1] >= b[start]) || (b[start] <= a[i] && b[start + 1] >= a[i]) || (start + 1 == finish && b[start] <= a[i + 1]) || (a[i] <= b[start] && i == n - 1)) && i < n)
		{
			b[finish] = a[i] + b[start];
			for (int j = 0; j < c[start].size(); j++)
			{
				len[c[start][j]]++;
				c[finish].push_back(c[start][j]);
			}
			q = c[start].size();
			for (int j = 0; j < q; j++)
				c[start].pop_back();
			len[i]++;
			c[finish].push_back(i);
			i++;
			finish++;
			start++;
		}
		else
		{
			b[finish] = b[start] + b[start + 1];
			for (int j = 0; j < c[start].size(); j++)
			{
				len[c[start][j]]++;
				c[finish].push_back(c[start][j]);
			}
			q = c[start].size();
			for (int j = 0; j < q; j++)
				c[start].pop_back();
			for (int j = 0; j < c[start + 1].size(); j++)
			{
				len[c[start + 1][j]]++;
				c[finish].push_back(c[start + 1][j]);
			}
			q = c[start + 1].size();
			for (int j = 0; j < q; j++)
				c[start + 1].pop_back();
		    finish++;
			start += 2;
		}
	}
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += a[i] * len[i];
	cout << sum;
	return 0;
}