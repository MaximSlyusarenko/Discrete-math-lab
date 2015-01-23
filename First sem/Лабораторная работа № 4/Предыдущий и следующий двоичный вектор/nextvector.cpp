#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

string s;

int main()
{
	freopen ("nextvector.in", "r", stdin);
	freopen ("nextvector.out", "w", stdout);
	cin >> s;
	int k = -1;
	for (int i = s.size() - 1; i >= 0; i--)
		if (s[i] == '1')
		{
			k = i;
			break;
		}
	if (k == -1)
		cout << "-" << endl;
	else
	{
		string s1 = "";
		for (int i = 0; i < s.size(); i++)
		{	
			if (i < k)
				s1 += s[i];
			else
			{
				if (s[i] == '0')
					s1 += "1";
				else
					s1 += "0";
			}
		}
		cout << s1 << endl;
	}
	k = -1;
	for (int i = s.size() - 1; i >= 0; i--)
		if (s[i] == '0')
		{
			k = i;
			break;
		}
	if (k == -1)
		cout << "-" << endl;
	else
	{
		string s1 = "";
		for (int i = 0; i < s.size(); i++)
		{
			if (i < k)
				s1 += s[i];
			else
			{
				if (s[i] == '0')
					s1 += "1";
				else
					s1 += "0";
			}
		}
		cout << s1 << endl;
	}
	return 0;
}