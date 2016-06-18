#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int n, q0 = 0, q1 = 0;
vector <string> a;
bool flag[1000];

void gen(string s)
{
	if (q0 == n && q1 == n)
	{
		a.push_back(s);
		return;
	}
	if (q0 < n)
	{
		string s1 = s + "(";
		q0++;
		gen(s1);
		q0--;
	}
	if (q1 < n)
	{
		string s1 = s + ")";
		q1++;
		gen(s1);
		q1--;
	}
}

int main()
{
	freopen ("brackets.in", "r", stdin);
	freopen ("brackets.out", "w", stdout);
	cin >> n;
	string s2 = "";
	gen(s2);
	for (int i = 0; i < a.size(); i++)
		flag[i]= true;
	int r0 = 0, r1 = 0;
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < a[i].size(); j++)
		{
			if (a[i][j] == '(')
				r0++;
			else
				r1++;
			if (r1 > r0)
				flag[i] = false;
		}
	}
	for (int i = 0; i < a.size(); i++)
		if (flag[i])
			cout << a[i] << endl;;
	return 0;
}