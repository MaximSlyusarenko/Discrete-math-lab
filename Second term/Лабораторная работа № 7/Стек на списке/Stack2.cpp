#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>

using namespace std;

struct stack2
{
	int c;
	stack2 *next;
};

stack2 *s = NULL, *tmp;
int n;

void add(int p)
{
	stack2 *tmp1;
	tmp1 = new stack2;
	if (s == NULL)
	{
		tmp1 -> c = p;
		tmp1 -> next = NULL;
		tmp = tmp1;
		s = tmp1;
	}
	else
	{
		tmp1 -> c = p;
		tmp1 -> next = tmp;
		tmp = tmp1;
		s = tmp;
	}
}

int main()
{
	freopen ("stack2.in", "r", stdin);
	freopen ("stack2.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		char c;
		cin >> c;
		if (c == '+')
		{
			int k;                               
			cin >> k;
			add(k);
		}
		else if (c == '-')
		{
			cout << tmp -> c << endl;
			s = s -> next;
			tmp = s;
		}
	}
	return 0;
}