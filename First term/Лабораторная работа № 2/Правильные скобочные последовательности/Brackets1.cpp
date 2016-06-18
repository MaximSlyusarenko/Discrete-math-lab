#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int n, q0 = 0, q1 = 0;
string s;

void gen(string s, int b, int q0, int q1)
{
	if (q0 == n && q1 == n)
	{
		cout << s << endl;
		return;
	}
	if (q0 < n)
	{
		string s1 = s + "(";
		gen(s1, b + 1, q0 + 1, q1);
	}
	if (q1 < n && b > 0)
	{
		string s1 = s + ")";
		gen(s1, b - 1, q0, q1 + 1);
	}
}

int main()
{
	freopen ("brackets.in", "r", stdin);
	freopen ("brackets.out", "w", stdout);
	cin >> n;
	s = "";
	gen(s, 0, 0, 0);
	return 0;
}