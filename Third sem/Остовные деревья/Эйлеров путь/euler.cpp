#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <fstream>
#include <stdexcept>

using namespace std;

int n, d, deg[2000], g[2000][2000];
vector <int> ans, a, st;

int main()
{
	freopen ("euler.in", "r", stdin);
	freopen ("euler.out", "w", stdout);
	cin >> n;	
	int kol = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> d;
		deg[i] = d;
		if (deg[i] % 2 != 0)
		{
			kol++;
		}
		for (int j = 0; j < d; j++)
		{
			int a;
			cin >> a;
			g[i][a]++;
		}
	}
	if (kol % 2 != 0)
	{
		cout << -1;
		return 0;
	}
	if (kol == 2)
	{
		for (int i = 1; i <= n; i++)
		{
			if (deg[i] % 2 != 0)
			{
				a.push_back(i);
			}
		}
		g[a[0]][a[1]]++;
		g[a[1]][a[0]]++;
	}
	st.push_back(1);
	while (!st.empty())
	{
		int v = st[st.size() - 1];
		if (deg[v] == 0)
		{
			ans.push_back(v);
			st.pop_back();
		}
		else
		{
			int i;
			for (int j = 1; j <= n; j++)
			{
				if (g[v][j] != 0)
				{
					i = j;
					break;
				}
			}
			g[v][i]--;
			g[i][v]--;
			deg[v]--;
			deg[i]--;
			st.push_back(i);
		}
	}
	if (kol == 2)
	{
		vector <int> res;
		for (int i = 0; i < ans.size() - 1; i++)
		{
			if ((ans[i] == a[0] && ans[i + 1] == a[1]) || (ans[i] = a[1] && ans[i + 1] == a[0]))
			{
				for (int j = i + 1; j < ans.size(); j++)
				{
					res.push_back(ans[j]);
				}
				for (int j = 1; j <= i; j++)
				{
					res.push_back(ans[j]);
				}
				break;
			}
		}
		cout << res.size() - 1 << endl;
		for (int i = 0; i < res.size(); i++)
		{
			cout << res[i] << " ";
		}
		return 0;
	}
	cout << ans.size() - 1 << endl;
	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i] << " ";
	}
	return 0;
}