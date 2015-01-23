#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	for (int i = 1000; true; i++)
	{
		int q = 0;
		for (int j = 1; j <= i; j++)
			if (i % j == 0)
				q++;
		if (q == 2)
		{
			cout << i;
			return 0;
		}
	}
	return 0;
}