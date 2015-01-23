#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string s;
vector <string> d;

int findk(string p)
{
	for (int i = 0; i < d.size(); i++)
		if (d[i] == p)
			return i;
	return -1;
}

int main()
{
	freopen ("lzw.in", "r", stdin);
	freopen ("lzw.out", "w", stdout);
	cin >> s;
	for (int i = 0; i < 26; i++)
	{
		string c = "";
		c += char(int('a' + i));
		d.push_back(c);
	}
	string k = "";
	int n = s.size();
	int num = -1;
	int i = 0;
	while (i < n)
	{
		k += s[i];
	    int l = findk(k);
	    if (l == -1)
	    {
	    	cout << num << " ";
	    	d.push_back(k);
	    	k = "";
	    }
	    else
	    {
	    	num = l;
	    	i++;
	    }
	}
	if (num != -1)
		cout << num;
	return 0;
}					