#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>

using namespace std;

int n;

int main()
{
	freopen ("brackets.in", "r", stdin);
	freopen ("brackets.out", "w", stdout);
	string s;
	while (cin >> s)
	{
		int tmp = 0, size = 10;
		char *a = new char[10];
		bool flag = true;
		for (int j = 0; j < s.size(); j++)
		{
			if (s[j] == '(' || s[j] == '[')
			{
				if (tmp + 1 == size)
				{
					char *e = new char[2 * size];
					for (int j = 0; j < size; j++)
						e[j] = a[j];
					a = e;
					size *= 2;
				}
				a[tmp] = s[j];
				tmp++;
			}
			if (s[j] == ')')
			{
				tmp--;
				if (a[tmp] != '(')
				{
					cout << "NO" << endl;
					flag = false;
					break;
				}
			}
			if (s[j] == ']')
			{
				tmp--;
				if (a[tmp] != '[')
				{
					cout << "NO" << endl;
					flag = false;
					break;
				}
			}
		}
		if (flag && tmp == 0)
			cout << "YES" << endl;
		if (flag && tmp != 0)
			cout << "NO" << endl;
	}
	return 0;
}