#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>

using namespace std;

int dp[5010][5010];
string s, t;

int main()
{
	freopen ("levenshtein.in", "r", stdin);
	freopen ("levenshtein.out", "w", stdout);
	cin >> s >> t;
	for (int i = 0; i <= s.size(); i++)
		dp[i][0] = i;
	for (int i = 0; i <= t.size(); i++)
		dp[0][i] = i;
	for (int i = 1; i <= s.size(); i++)
		for (int j = 1; j <= t.size(); j++)
		{
			dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;
			if (s[i - 1] == t[j - 1])
				dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
			else
				dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
		}
	cout << dp[s.size()][t.size()];
	return 0;
}