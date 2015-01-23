#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n, m, k, b, c[1000][5];
vector <string> a;

void gen(string s)
{
	if (s.size() == n)
		a.push_back(s);
	else
	{
		string s1 = s + "0";
		gen(s1);
		string s2 = s + "1";
		gen(s2);
	}
}					 

int main()
{
	freopen ("netcheck.in", "r", stdin);
	freopen ("netcheck.out", "w", stdout);
	cin >> n >> m >> k;
	int r = 0;
	for (int i = 0; i < k; i++)
	{
		cin >> b;
		for (int j = 0; j < b; j++)
		{
			cin >> c[r][1] >> c[r][2];
			if (c[r][1] > c[r][2])
			{
				int t = c[r][1];
				c[r][1] = c[r][2];
				c[r][2] = t;
			}
			r++;
		}
	}
	string s = "";
	gen(s);
	for (int i = 0; i < a.size(); i++)
	{
		//cerr << a[i] << " ";
		for (int j = 0; j < r; j++)
			if (a[i][c[j][1] - 1] > a[i][c[j][2] - 1])
			{
				char t = a[i][c[j][1] - 1];
				a[i][c[j][1] - 1] = a[i][c[j][2] - 1];
				a[i][c[j][2] - 1] = t;
			}
		for (int j = 0; j < a[i].size() - 1; j++)
			if (a[i][j] > a[i][j + 1])
			{
				cout << "No";
				//cerr << a[i] << endl;
				return 0;
			}
		//cerr << endl;
	}
	cout << "Yes";
	return 0;
}
	