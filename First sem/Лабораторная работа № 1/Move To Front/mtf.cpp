#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

string s;
int a[1001];

int main()
{
	freopen ("mtf.in", "r", stdin);
	freopen ("mtf.out", "w", stdout);
	cin >> s;
	int n = s.size();
	for (int i = 0; i < n; i++)
		a[i] = i + 1;
	for (int i = 0; i < n; i++)
	{
		int k = int(s[i]) - int ('a');
		cout << a[k] << " ";
		for (int i = 0; i < 26; i++)
			if (a[i] < a[k])
				a[i]++;
		a[k] = 1;			
	}
	return 0;
}			 