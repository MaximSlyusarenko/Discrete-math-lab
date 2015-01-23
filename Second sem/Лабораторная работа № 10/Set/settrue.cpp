#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

struct mylist {
    int value;
    mylist *prev;
    mylist *next;
};

mylist *a[20011];

int main()
{
	ifstream in ("set.in");
	ofstream out ("set.out");
	int n = 20011, k;
	string s;
	for (int i = 0; i < n; i++)
		a[i] = NULL;
	while (in >> s >> k)
	{
		if (s == "insert")
		{
			int h = abs(k % n);
			if (a[h] == NULL)
			{
				mylist *tmp = new mylist;
				tmp -> value = k;
				tmp -> next = NULL;
				tmp -> prev = NULL;
				a[h] = tmp;
			}
			else
			{                   
				mylist *tmp = a[h];	
				while (tmp -> next != NULL && tmp -> value != k)
					tmp = tmp -> next;
				bool flag = true;
				if (tmp -> value == k)
					flag = false;
				if (flag)
				{
					mylist *tmp1 = new mylist;
					tmp1 -> value = k;
					tmp1 -> next = NULL;
					tmp1 -> prev = tmp;
					tmp -> next = tmp1;
				}
			}
		}
		if (s == "delete")
		{                          
			int h = abs(k % n);
			if (a[h] != NULL)
			{
				mylist *tmp = a[h];
				while (tmp != NULL && tmp -> value != k)
					tmp = tmp -> next;
				if (tmp != NULL)
				{
					mylist *tmp1 = tmp -> prev;
					mylist *tmp2 = tmp -> next;
					if (tmp1 == NULL)
					{
						if (tmp2 != NULL)
							tmp2 -> prev = NULL;
						a[h] = tmp2;
					}
					else
					{
						if (tmp2 == NULL)
						{
							tmp1 -> next = NULL;
						}
						else
						{
							tmp1 -> next = tmp2;
							tmp2 -> prev = tmp1;
						}
					}
				}
			}
		}
		if (s == "exists")
		{
			int h = abs(k % n);
			if (a[h] == NULL)
			{
				out << "false" << endl;
			}
			else
			{
				mylist *tmp = a[h];
				while (tmp != NULL && tmp -> value != k)
					tmp = tmp -> next;
				if (tmp == NULL)
					out << "false" << endl;
				else
					out << "true" << endl;
			}
		}
	}
	return 0;
}