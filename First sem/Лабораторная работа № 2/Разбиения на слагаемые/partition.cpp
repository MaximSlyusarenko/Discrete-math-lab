#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n, a[50];

void gen(int pos, int sum, int prev)
{
	if (sum == n)
	{
		for (int i = 0; i < pos - 1; i++)
			cout << a[i] << "+";
		cout << a[pos - 1] << endl;
		return;
	}
	for (int i = max(prev, 1); i + sum <= n; i++)
	{
		int k = sum + i; 
		a[pos] = i;
		gen(pos + 1, k, i);
	}
}

int main()
{
	freopen ("partition.in", "r", stdin);
	freopen ("partition.out" ,"w", stdout);
	cin >> n;
	gen(0, 0, 0);
	return 0;
}