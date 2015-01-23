#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>

using namespace std;

int n, size = 10, cur = 0, start = 0, t[20], r[50];
unsigned short *a = new unsigned short [10]; // по условию тип очереди unsigned short
string c[200000], s[200000];

void push(int q)
{                          
	if (cur + 1 == size)                         
	{                                            
		unsigned short *e = new unsigned short [2 * size];              
		for (int j = 0; j < cur - start; j++)    
			e[j] = a[j + start];                 
		a = e;                                   
		cur = cur - start;                       
		start = 0;                               
		size *= 2;                               
	}                                            
	a[cur] = q;
	cur++;
}

int pop()
{
	int result = a[start];
	start++;
	return result;
}

int main()
{
	freopen ("quack.in", "r", stdin);
	freopen ("quack.out", "w", stdout);
	t[0] = 1;
	for (int i = 1; i <= 10; i++)
		t[i] = t[i - 1] * 10;
	int i = 0;
	while (cin >> s[i])
		i++;
	int n = i;
	for (int i = 0; i < n; i++)
		if (s[i][0] == ':')
			c[i] = s[i].substr (1, s[i].size() - 1);
	i = 0;
	while (i < n)
	{
		if (s[i][0] >= '0' && s[i][0] <= '9')
		{
			int d = 0;
			for (int j = s[i].size() - 1; j >= 0; j--)
				d += (int (s[i][j]) - int ('0')) * t[s[i].size() - 1 - j];
			push(d);
		}
		if (s[i][0] == '+')
		{
			unsigned short p = pop();
			unsigned short q = pop();
			int f = p + q;
			push(f);
		}
		if (s[i][0] ==	'-')
		{
			unsigned short p = pop();
			unsigned short q = pop();
			int f = p - q;
			push(f);
		}
		if (s[i][0] == '/')
		{
			unsigned short p = pop();
			unsigned short q = pop();
			if (p == 0 && q == 0)
				push(0);
			else
			{
				if (p / q < 0 && p % q != 0)
					push (p / q - 1);
				else
					push(p / q);
			}
		}
		if (s[i][0] == '*')
		{
			unsigned short p = pop();
			unsigned short q = pop();
			unsigned short f = p * q;
			push(f);
		}
		if (s[i][0] == '%')
		{
			unsigned short p = pop();
			unsigned short q = pop();
			if (p == 0 && q == 0)
				push(0);
			else
			{
				push(p % q);
			}
		}
		if (s[i][0] == '>')
		{
			unsigned short q = pop();
			r[int (s[i][1]) - int ('a')] = q;
		}
		if (s[i][0] == '<')
		{
			int q = r[int (s[i][1]) - int ('a')];
			push(q);
		}
		if (s[i][0] == 'P' && s[i]. size() == 1)
		{
			unsigned short q = pop();
			cout << q << endl;
		}
		if (s[i][0] == 'P' && s[i].size() > 1)
		{
			int q = r[int (s[i][1]) - int ('a')];
			cout << q << endl;
		}		
		if (s[i][0] == 'C' && s[i].size() == 1)
		{
			unsigned short q = pop();
			cout << char (q % 256);
		}
		if (s[i][0] == 'C' && s[i].size() > 1)
		{
			int q = r[int (s[i][1]) - int ('a')];
			cout << char (q % 256);
		}
		if (s[i][0] == 'J')
		{
			string t = s[i].substr (1, s[i].size() - 1);
			for (int j = 0;	j < n; j++)
				if (s[j][0] == ':')
				{
					if (t == c[j])
						i = j;
				}
		}
		if (s[i][0] == 'Z')
		{
			string t = s[i].substr (2, s[i].size() - 2);
			if (r[int (s[i][1]) - int ('a')] == 0)
				for (int j = 0; j < n; j++)
					if (s[j][0] == ':')
						if (t == c[j])
							i = j;
		}
		if (s[i][0] == 'E')
		{
			string t = s[i].substr (3, s[i].size() - 3);
			if (r[int (s[i][1]) - int ('a')] == r[int (s[i][2]) - int ('a')])
				for (int j = 0; j < n; j++)
					if (s[j][0] == ':')
						if (t == c[j])
							i = j;
		}
		if (s[i][0] == 'G')
		{
			string t = s[i].substr (3, s[i].size() - 3);
			if (r[int (s[i][1]) - int ('a')] > r[int (s[i][2]) - int ('a')])
				for (int j = 0; j < n; j++)
					if (s[j][0] == ':')
						if (t == c[j])
							i = j;
		}
		if (s[i][0] == 'Q')
			return 0;
		i++;
	}																																			
	return 0;
}