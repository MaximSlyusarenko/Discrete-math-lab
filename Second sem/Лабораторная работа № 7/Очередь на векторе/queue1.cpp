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
	freopen ("queue1.in", "r", stdin);
	freopen ("queue1.out", "w", stdout);
	scanf ("%d", &n);
	int cur = 0, start = 0;
	for (int i = 1; i <= 2 * n; i++)
	{
		char c;
		scanf ("%c", &c);
		if (c == '+')
		{
			int q;
			scanf ("%d", &q);
			if (cur + 1 == size)
			{
				int *e = new int[2 * size];
				size = 2 * size;
				for (int j = 0; j < cur - start; j++)
					e[j] = a[j + start];
				delete [] a;
				a = e;
				cur = cur - start;
				start = 0;
			}
			a[cur] = q;
			cur++;
		}
		if (c == '-')
		{
			printf ("%d\n", a[start]);
			start++;
			if ((cur - start) * 4 < size && cur > start)
			{
				size /= 2;
				int *e = new int[size];
				for (int j = 0; j < cur - start; j++)
					e[j] = a[j + start];
				delete [] a;
				a = e;
				cur = cur - start;
				start = 0;
			}
		}
	}
	return 0;
}