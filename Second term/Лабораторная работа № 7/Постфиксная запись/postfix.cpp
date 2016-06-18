#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>

using namespace std;

int t[20], tmp = 0;
int *a = new int[10];

int main()
{
	freopen ("postfix.in", "r", stdin);
	freopen ("postfix.out", "w", stdout);
	string c;
	t[0] = 1;
	for (int i = 1; i <= 10; i++)
		t[i] = 10 * t[i - 1];
	while (cin >> c)
	{
		int size = 10;
		if (c[0] >= '0' && c[0] <= '9')
		{
			if (tmp + 1 == size)
			{
				int *e = new int[2 * size];
				for (int j = 0; j < size; j++)
					e[j] = a[j];
				a = e;
				size *= 2;
			}
			int d = 0;
			for (int i = c.size() - 1; i >= 0; i--)
				d += (int (c[i]) - int ('0')) * t[c.size() - i - 1];
			a[tmp] = d;
			tmp++;
		}
		if (c[0] == '+')
		{
			tmp--;
			int q = a[tmp];
			tmp--;
			int r = a[tmp];
			a[tmp] = q + r;
			tmp++;
		}
		if (c[0] == '-')      
		{                     
			tmp--;            
			int q = a[tmp];   
			tmp--;            
			int r = a[tmp];   
			a[tmp] = r - q;   
			tmp++;
		}
		if (c[0] == '*')      
		{                     
			tmp--;            
			int q = a[tmp];   
			tmp--;            
			int r = a[tmp];   
			a[tmp] = q * r;   
			tmp++;            
		}            
	}
	cout << a[tmp - 1];
	return 0;		                              
}