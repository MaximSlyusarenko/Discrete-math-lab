#include <cstdio>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

int main()
{
	freopen("multimap.in", "w", stdout);
	
	srand((double)time(NULL));
	
	int n = rand()%100000;

	for (int i = 0; i < n; i++)
	{            
		int fl = rand()%5;
		
		string s = "", t = "";

		int q = 1 + rand()%19;
		for (int i = 0; i < q; i++)
		{
			int k = rand()%26;
			char c = char(k + int('a'));
			s += c;
		}

		int p = 1 + rand()%19;
		for (int i = 0; i < p; i++)
		{
			int v = rand()%26;
			char c = char(v + int('a'));
			t += c;
		}

		if (fl == 0)
		{
			cout << "put ";
			cout << s << " " << t << endl;
		}
		if (fl == 1)
			cout << "get " << s << endl;
		if (fl == 2)
			cout << "deleteall " << s << endl;
		if (fl == 3)
			cout << "delete " << s << " " << t << endl;	 
	}

	return 0;
}