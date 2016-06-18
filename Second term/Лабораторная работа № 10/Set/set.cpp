#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

int n = 1000003, a[2000000];

void delet(int h, int k)
{
	int j = h + 1;
	if (j > n)
		j = 0;
	while (a[j] != 0 || a[j] != k)
	{
		if (a[j] == 0)
		{
			a[h] = 0;
			return;
		}
		j++;
		if (j > n)
			j = 0;
	}
	a[h] = a[j];
	delet(j, k);
}

int main()
{
	ifstream in ("set.in");
	ofstream out ("set.out");
	string s;
	int k;
	for (int i = 0; i <= n; i++)
		a[i] = 0;
	while (in >> s >> k)
	{
		if (s == "insert")
		{
			int h = k % n;
			while (a[h] != 0 && a[h] != k)
			{
				h++;
				if (a[h] > n)
					h = 0;
			}
			a[h] = k;
		}
		if (s == "exists")
		{
			int h = k % n;
			int i = h;
			while (a[i] != 0 && i != h && a[i] != k)
			{
				i++;
				if (i > n)
					i = 0;
			}
			if (a[i] == k)
				out << "true" << endl;
			else
				out << "false" << endl;
		}
		if (s == "delete")
		{
			int h = k % n;
			delet(h, k);
		}
	}
	return 0;
}