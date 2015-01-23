#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int n, a[10];
bool used[10];

void gen(int pos)
{
	if (pos == n)
	{
		for (int i = 0; i < n; i++)
			cout << a[i] << " ";
		cout << endl;
	}
	else
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
	freopen ("permutations.in", "r", stdin);
	freopen ("permutations.out", "w", stdout);
	cin >> n;	
	for (int i = 1; i <= n; i++)
		used[i] = false;
	gen(0);
	return 0;
}
	