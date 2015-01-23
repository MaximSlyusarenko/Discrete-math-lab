#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

string s[200000], t[200000];
int p[200000], q[200000];

int main()
{
	ifstream in ("multimap.out");
	int i = 0;
	while (in >> p[i] >> s[i])
	{
		if (p[i] != 0)
			in >> s[i];
		i++;
	}
	in.close();
	ifstream rin ("multimap1.out");
	int j = 0;
	while (rin >> q[j] >> t[j])
	{
		if (q[j] != 0)
			in >> t[j];
		j++;
	}
	if (i != j)
	{
		ofstream out ("error.err");
		out << "1" << endl;
		return 0;
	}
	for (int i = 0; i < j; i++)
	{
		bool flag = true;
		for (int k = 0; k < j; k++)
			if (s[i] == t[k])
				flag = false;
		if (flag)
		{
			ofstream out ("error.err");
			out << i << endl;
		}
	}
	/*for (int i = 0; i < j; i++)
		if (p[i] != q[i] || s[i] != t[i])
		{
			ofstream out ("error.err");
			out << "2 " << i << endl;
			return 0;
		}*/
	return 0;
}