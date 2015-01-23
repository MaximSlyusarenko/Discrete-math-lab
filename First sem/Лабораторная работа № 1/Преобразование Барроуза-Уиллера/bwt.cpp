#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

string s, a[1001];

int main()
{
	freopen ("bwt.in", "r", stdin);
	freopen ("bwt.out", "w", stdout);
	cin >> s;
	a[0] = s;
	for (int i = 1; i < s.size(); i++)
	{
		string k = a[i - 1];
		char r = k[k.size() - 1];
		for (int j = k.size() - 1; j >= 1; j--)
			k[j] = k[j - 1];
		k[0] = r;
		a[i] = k;
	}
	sort(a, a + s.size());
	for (int i = 0; i < s.size(); i++)
		cout << a[i][s.size() - 1];
	return 0;
}