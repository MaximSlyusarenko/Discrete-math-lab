#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int n, a[10];
bool used[10];

void gen(int pos)
{
	bool flag = true;
	for (int i = 0; i < pos - 1; i++)
		if (a[i] > a[i + 1])
			flag = false;
	if (flag)
	{
		for (int i = 0; i < pos; i++)
			cout << a[i] << " ";
		cout << endl;
	}
	for (int i = 1; i <= n; i++)	
	{
		if (!used[i])
		{
			a[pos] = i;
			used[i] = true;
			gen(pos + 1);
			used[i] = false;
		}
	}
}
		 		             
int main()
{
	freopen ("subsets.in", "r", stdin);
	freopen ("subsets.out", "w", stdout);
	cin >> n;	
	for (int i = 1; i <= n; i++)
		used[i] = false;
	gen(0);
	return 0;
}
	