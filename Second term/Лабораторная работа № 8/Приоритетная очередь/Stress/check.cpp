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

int main()
{
	ifstream in ("priorityqueue.out");
	int i = 0;
	while (in >> s[i])
		i++;
	in.close();
	ifstream rin ("priorityqueue1.out");
	int j = 0;
	while (rin >> t[j])
		j++;
	if (i != j)
	{
		ofstream out ("error.err");
		out << "1" << endl;
		return 0;
	}
	for (int i = 0; i < j; i++)
		if (s[i] != t[i])
		{
			ofstream out ("error.err");
			out << "2 " << i << endl;
			return 0;
		}
	return 0;
}