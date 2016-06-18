#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int n, m, dp[2001][2001], a[10000], b[10000];
vector <int> ans;

int main()
{
	freopen ("lcs.in", "r", stdin);
	freopen ("lcs.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	cin >> m;
	for (int i = 1; i <= m; i++)
		cin >> b[i];
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			dp[i][j] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (a[i] == b[j])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
		}
	int p = n, q = m;
	while (p > 0 && q > 0)
	{
		if (dp[p][q] == dp[p - 1][q])
			p--;
		else
		if (dp[p][q] == dp[p][q - 1])
			q--;
		else
		if (dp[p][q] == dp[p - 1][q - 1] + 1)
		{
			ans.push_back(a[p]);
			p--;
			q--;
		}
	}
	cout << ans.size() << endl;
	reverse(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " ";
	return 0;
}