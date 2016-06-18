#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

long long n, a[1000];
vector <long long> c[3], b;
vector <bool> flag[3];
string s[1000], str[1000];

int main()
{
	freopen ("huffman.in", "r", stdin);
	freopen ("huffman.out", "w", stdout);
	cin >> n;       
	for (int i = 0; i < n; i++)
		cin >> a[i];
	sort(a, a + n);
	int i = 0;
	int start = 0, finish = 0;
	while ((i < n && start <= finish) || start + 1 != finish)
	{
		if (i + 1 < n && (start == finish || (a[i] <= b[start] && a[i + 1] <= b[start])))
		{
			b.push_back(a[i] + a[i + 1]);
			c[1].push_back(i);
			c[2].push_back(i + 1);
			flag[1].push_back(true);
			flag[2].push_back(true);
			i += 2;
			finish++;
		}
		else if (i < n && ((a[i] <= b[start] && a[i + 1] >= b[start]) || (b[start] <= a[i] && b[start + 1] >= a[i]) || (start + 1 == finish && b[start] <= a[i + 1]) || (a[i] <= b[start + 1] && i == n - 1)))
		{
			b.push_back(a[i] + b[start]);
			c[1].push_back(i);
			flag[1].push_back(true);
			c[2].push_back(start);
			flag[2].push_back(false);
			i++;
			finish++;
			start++;
		}
		else
		{
			b.push_back(b[start] + b[start + 1]);
			c[1].push_back(start);
			flag[1].push_back(false);
			c[2].push_back(start + 1);
			flag[2].push_back(false);
		    finish++;
			start += 2;
		}
	}
	int k = b.size();
	str[k - 1] = "";
	for (int i = k - 1; i >= 0; i--)
	{
		if (!flag[1][i])
			str[c[1][i]] = str[i] + "0";
		else
			s[c[1][i]] = str[i] + "0";
		if (!flag[2][i])
			str[c[2][i]] = str[i] + "1";
		else
			s[c[2][i]] = str[i] + "1";
	}
	long long sum = 0;
	for (int i = 0; i < n; i++)
	{
		long long len = s[i].size();
		sum += a[i] * len;
	}
	cout << sum;
	return 0;
}