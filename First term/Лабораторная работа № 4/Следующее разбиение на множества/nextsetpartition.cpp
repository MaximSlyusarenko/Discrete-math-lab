#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

long long n, k, a[2000][2000];

int main()
{
	ifstream in ("nextsetpartition.in");
	ofstream out ("nextsetpartition.out");
	in >> n >> k;
	int i = 0;
	while (n != 0 && k != 0)
	{
		int j = 0;
		while (in.get() != '/n')
		{
			in >> a[i][j];
			j++;
		}
		for (int p = 0; p < j; p++)
			out << a[i][p];
		out << endl;
		if (i == k - 1)
		{
			in >> n >> k;
			i = -1;
		}
		i++;
	}
	return 0;
}