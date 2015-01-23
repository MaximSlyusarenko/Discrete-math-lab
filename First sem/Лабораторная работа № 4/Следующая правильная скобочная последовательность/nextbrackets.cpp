#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

string s;

int main()
{
	freopen ("nextbrackets.in", "r", stdin);
	freopen ("nextbrackets.out", "w", stdout);
	cin >> s;
	int n = s.size() - 1, b = 0;
	int h = -1;
	for (int i = n; i > 0; i--)
	{
		if (s[i] == ')')
			b++;
		else
		if (s[i] == '(' && b - 1 == 0)
			b--;
		else
		if (s[i] == '(' && b - 1 > 0)
		{
			s[i] = ')';
			h = i;
		}
	}
	if (h == -1)
	{
		cout << "-";
		return 0;
	}
	int q0 = 0, q1 = 0;
	for (int i = 0; i <= h; i++)
	{
		cout << s[i];
		if (s[i] == '(')
			q0++;
		else
			q1++;
	}
	for (int i = q0 + 1; i <= (n + 1) / 2; i++)
		cout << "(";
	for (int i = q1 + 1; i <= (n + 1) / 2; i++)
		cout << ")";
	return 0;
}