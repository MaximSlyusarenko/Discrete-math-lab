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
    string key;
    string value;
    mylist *prev;
    mylist *next;
    mylist *nextInput;
    mylist *prevInput;
};

mylist *a[21000];
long long h[200000];
string p[200000], b[200000], t[200000];

int main()
{
	ifstream in ("linkedmap.in");
	ofstream out ("linkedmap.out");
	int n = 20011, k;
	string s;
	for (int i = 0; i < n; i++)
		a[i] = NULL;
	int i = 0;
	mylist *last = NULL;
	// last - последний добавленный элемент из входных данных
	while (in >> b[i])
	{
		if (b[i] == "put")
		{
			in >> t[i] >> p[i];
			long long q = 3;
			for (int j = 0; j < t[i].size(); j++)
			{
				h[i] += (int(t[i][j]) - int('a')) * q;
				h[i] %= n;
				q *= 3;
			}
		}
		if (b[i] == "delete")
		{
			in >> t[i];
			long long q = 3;                       
			for (int j = 0; j < t[i].size(); j++)     
			{                                      
				h[i] += (int(t[i][j]) - int('a')) * q;
				h[i] %= n;                         
				q *= 3;                            
			}                                      
		}
		if (b[i] == "get" || b[i] == "next" || b[i] == "prev")
		{
			in >> t[i];
			long long q = 3;                       
			for (int j = 0; j < t[i].size(); j++)     
			{                                      
				h[i] += (int(t[i][j]) - int('a')) * q;
				h[i] %= n;                         
				q *= 3;                            
			}
		}	                                   
		i++;
	}
	for (int j = 0; j < i; j++)
	{
		if (b[j] == "put")
		{	
			if (a[h[j]] == NULL)
			{
				mylist *tmp = new mylist;
				tmp -> key = t[j];
				tmp -> value = p[j];
				tmp -> next = NULL;
				tmp -> prev = NULL;
				tmp -> nextInput = NULL;
				tmp -> prevInput = last;
				if (last != NULL)
					last -> nextInput = tmp;
				last = tmp;
				a[h[j]] = tmp;
			}
			else
			{                   
				mylist *tmp = a[h[j]];	
				while (tmp -> next != NULL && tmp -> key != t[j])
					tmp = tmp -> next;
				bool flag = true;
				if (tmp -> key == t[j])
				{
					flag = false;
					tmp -> value = p[j];
				}
				if (flag)
				{
					mylist *tmp1 = new mylist;
					tmp1 -> key = t[j];
					tmp1 -> value = p[j];
					tmp1 -> next = NULL;
					tmp1 -> prev = tmp;
					tmp -> next = tmp1;
					tmp1 -> nextInput = NULL;
					tmp1 -> prevInput = last;
					if (last != NULL)
						last -> nextInput = tmp1;
					last = tmp1;
				}
			}
		}
		if (b[j] == "delete")
		{                          
			if (a[h[j]] != NULL)
			{
				mylist *tmp = a[h[j]];
				while (tmp != NULL && tmp -> key != t[j])
					tmp = tmp -> next;
				if (tmp != NULL)
				{
					mylist *tmp1 = tmp -> prev;
					mylist *tmp2 = tmp -> next;
					if (tmp1 == NULL)
					{
						if (tmp2 != NULL)
							tmp2 -> prev = NULL;
						a[h[j]] = tmp2;
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
					if (tmp -> nextInput != NULL)
						(tmp -> nextInput) -> prevInput = tmp -> prevInput;
					else
						last = tmp -> prevInput;
					if (tmp -> prevInput != NULL)
						(tmp -> prevInput) -> nextInput = tmp -> nextInput;
				}
			}
		}
		if (b[j] == "get")
		{
			if (a[h[j]] == NULL)
			{
				out << "none" << endl;
			}
			else
			{
				mylist *tmp = a[h[j]];
				while (tmp != NULL && tmp -> key != t[j])
					tmp = tmp -> next;
				if (tmp == NULL)
					out << "none" << endl;
				else
					out << tmp -> value << endl;
			}
		}
		if (b[j] == "next")
		{
			if (a[h[j]] == NULL)
			{
				out << "none" << endl;
			}
			else
			{
				mylist *tmp = a[h[j]];
				while (tmp != NULL && tmp -> key != t[j])
					tmp = tmp -> next;
				if (tmp == NULL || tmp -> nextInput == NULL)
					out << "none" << endl;
				else
					out << (tmp -> nextInput) -> value << endl;
			}
		}
		if (b[j] == "prev")                                    
		{                                         
			if (a[h[j]] == NULL)                               
			{                                     
				out << "none" << endl;                         
			}                                                  
			else                                               
			{
				mylist *tmp = a[h[j]];                         
				while (tmp != NULL && tmp -> key != t[j])      
					tmp = tmp -> next;                         
				if (tmp == NULL || tmp -> prevInput == NULL)                               
					out << "none" << endl;                     
				else                                           
					out << (tmp -> prevInput) -> value << endl;
			}                                                  
		}
	}
	return 0;
}