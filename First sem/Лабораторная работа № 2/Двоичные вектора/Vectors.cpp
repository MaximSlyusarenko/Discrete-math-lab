#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string s;
int n;
vector <string> a;

void gen(string s)
{
	if (s.size() == n)
		a.push_back(s);
	else
	{
		string s1 = s + "0";
		gen(s1);
		if (s[s.size() - 1] != '1')
		{
			string s2 = s + "1";
			gen(s2);
		}
	}
}					 

int main()
{
	freopen ("vectors.in", "r", stdin);
	freopen ("vectors.out", "w", stdout);
	cin >> n;
	s = "";
	gen(s);
	cout << a.size() << endl;
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << endl;
	return 0;
}
	