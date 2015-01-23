#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n, a[200010], q, p;
char c;

int main()
{
	freopen ("nextpartition.in", "r", stdin);
	freopen ("nextpartition.out", "w", stdout);
	int r = 0;
	cin >> n >> c;
	while (cin >> a[r])
	{
		cin >> c;
		r++;
	}
	r--;
	if (r == 0)
	{
		cout << "No solution";
		return 0;
	}
	cout << n << "=";
	for (int i = 0; i < r - 1; i++)
		cout << a[i] << "+";
	p = a[r - 1] + 1;
	q = a[r] - 1;
	if (p > q)
	{	
		cout << p + q;
		return 0;
	}
	cout << p << "+";
	int e = q / p - 1;
	for (int i = 1; i <= e; i++)
		cout << p << "+";
	int d = q - p * e;
	cout << d;
	return 0;
}