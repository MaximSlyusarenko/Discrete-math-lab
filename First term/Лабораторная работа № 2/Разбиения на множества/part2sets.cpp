#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int n, k, a[20][20], kol[20], s[30][30];
bool used[20];

void gen(int pos, int r)
{
	if (pos == k)
	{
		int sum = 0;
		for (int i = 0; i < pos; i++)
			sum += kol[i];
		bool flag = true;
		for (int i = 0; i < pos; i++)
			if (kol[i] == 0 || (kol[i] > n - k + 1 && i < pos - 1))
				flag = false;
		if (sum == n && flag)
		{	 
			for (int i = 0; i < k; i++)
			{
				for (int j = 0; j < kol[i]; j++)
					cout << a[i][j] << " ";
				cout << endl;
			}
			cout << endl;
		}
		return;
	}
	for (int i = r; i <= n; i++)
		if (!used[i])
		{
			if (kol[pos] - 1 < 0 || a[pos][kol[pos] - 1] < i)
			{
				int mini = 1000000;
				for (int j = 0; j < kol[pos - 1]; j++)
					if (a[pos - 1][j] < mini)
						mini = a[pos - 1][j];
				if (i < mini && mini != 1000000)
					return;			
				a[pos][kol[pos]] = i;
				kol[pos]++;
				used[i] = true;
				gen(pos + 1, r);
				gen(pos, r);
				kol[pos]--;
				used[i] = false;
			}
		}
}

int main()
{
	freopen ("part2sets.in", "r", stdin);
	freopen ("part2sets.out", "w", stdout);
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
	{
		used[i] = false;
		kol[i - 1] = 0;
	}
	a[0][0] = 0;
	gen(0, 1);
	return 0;
}