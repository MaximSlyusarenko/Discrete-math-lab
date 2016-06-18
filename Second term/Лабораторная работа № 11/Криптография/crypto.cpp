#include <iostream>
#include <cmath>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <iomanip>

using namespace std;

int a[2000001][3][3], t[8000001][3][3], n, m, p;
	
struct matrix 
{
	int a;
	int b;
	int c;
	int d;
};

void sozd(int v, int l, int r)
{
	if (l == r)
	{
		t[v][1][1] = a[l][1][1];
		t[v][1][2] = a[l][1][2];
		t[v][2][1] = a[l][2][1];
		t[v][2][2] = a[l][2][2];
	}
	else
	{
		int k = (l + r) / 2;
		sozd(2 * v, l, k);
		sozd(2 * v + 1, k + 1, r);
		t[v][1][1] = (t[2 * v][1][1] * t[2 * v + 1][1][1] + t[2 * v][1][2] * t[2 * v + 1][2][1]) % p;	
		t[v][1][2] = (t[2 * v][1][1] * t[2 * v + 1][1][2] + t[2 * v][1][2] * t[2 * v + 1][2][2]) % p;
		t[v][2][1] = (t[2 * v][2][1] * t[2 * v + 1][1][1] + t[2 * v][2][2] * t[2 * v + 1][2][1]) % p;
		t[v][2][2] = (t[2 * v][2][1] * t[2 * v + 1][1][2] + t[2 * v][2][2] * t[2 * v + 1][2][2]) % p;
	}
}

matrix searchans(int v, int lk, int rk, int l, int r)
{
	matrix d;
	if (l > r)
	{
		d.a = 1;
		d.b = 0;
		d.c = 0;
		d.d = 1;
		return d;
	}
	if (lk == l && rk == r)
	{
		d.a = t[v][1][1];
		d.b = t[v][1][2];
		d.c = t[v][2][1];
		d.d = t[v][2][2];
		return d;
	}
	int k = (lk + rk) / 2;
	matrix b, c;
	b = searchans(2 * v, lk, k, l, min(k, r));
	c = searchans(2 * v + 1, k + 1, rk, max(k + 1, l), r);
	d.a = (b.a * c.a + b.b * c.c) % p;
	d.b = (b.a * c.b + b.b * c.d) % p;
	d.c = (b.c * c.a + b.d * c.c) % p;
	d.d = (b.c * c.b + b.d * c.d) % p;
	return d;
}

int main()
{
	std::ios_base::sync_with_stdio(0);
	freopen ("crypto.in", "r", stdin);
	freopen ("crypto.out", "w", stdout);
	matrix d;
	int l, r;
	cin >> p >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i][1][1] >> a[i][1][2] >> a[i][2][1] >> a[i][2][2];
		a[i][1][1] %= p;
		a[i][1][2] %= p;
		a[i][2][1] %= p;
		a[i][2][2] %= p;
	}
	sozd(1, 1, n);
	for (int i = 0; i < m; i++)
	{
		cin >> l >> r;
		d = searchans(1, 1, n, l, r);
		cout << d.a << " " << d.b << endl << d.c << " " << d.d << endl << endl;
	}
	return 0;
}