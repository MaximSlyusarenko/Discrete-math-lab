#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>

using namespace std;

int n, size = 10;
int *a = new int[10];

int main()
{
	freopen ("stack1.in", "r", stdin);
	freopen ("stack1.out", "w", stdout);
	scanf ("%d", &n);
	int tmp = 0;
	for (int i = 1; i <= 2 * n; i++)
	{
		char c;
		scanf ("%c", &c);
		if (c == '+')
		{
			int k;
			scanf ("%d", &k);
			if (tmp + 1 == size)
			{
				int *e = new int[2 * size];
				for (int j = 0; j < size; j++)
					e[j] = a[j];
				a = e;
				size *= 2;
			}
			a[tmp] = k;
			tmp++;
		}
		if (c == '-')
		{
			tmp--;
			printf ("%d\n", a[tmp]);
		}
	}
	return 0;
}