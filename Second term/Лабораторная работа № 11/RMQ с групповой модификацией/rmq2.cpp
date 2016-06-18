#include <iostream>
#include <cmath>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <iomanip>

using namespace std;

int a[100001], t[400001], n, m, mod1[400001], mod2[400001];
	
void sozd(int v, int l, int r)
{
	if (l == r)
	{
		t[v] = a[l];
	}
	else
	{
		int k = (l + r) / 2;
		sozd(2 * v, l, k);
		sozd(2 * v + 1, k + 1, r);
		if (t[2 * v + 1] < t[2 * v])
		{
			t[v] = t[2 * v + 1];	
		}
		else
		{
			t[v] = t[2 * v];
		}
	}
	mod1[v] = 0;
	mod2[v] = 0;
}

void push(int v, int l, int r)
{
	if (l == r)
		return;
	mod1[2 * v] = mod1[v];
	//t[2 * v] = t[v] + mod2[2 * v];
	mod1[2 * v + 1] = mod1[v];
	//t[2 * v + 1] = t[v] + mod2[2 * v + 1];
}

int searchmin(int v, int lk, int rk, int l, int r)
{
	int d;
	if (l > r)
	{
		d = 1000000001;
		return d;
	}
	if (lk == l && rk == r)
	{
		d = t[v];
		return d;
	}
	push(v, lk, rk);
	int k = (lk + rk) / 2;
	int b, c;
	b = searchmin(2 * v, lk, k, l, min(k, r)) + mod2[v];
	c = searchmin(2 * v + 1, k + 1, rk, max(k + 1, l), r) + mod2[v];
	d = min(b, c);
	return d;
}

void modify(int v)
{
	while (v > 1)
	{
		v /= 2;
		if (mod1[v])
			t[v] = min(mod1[v] + mod2[2 * v], mod1[v] + mod2[2 * v + 1]);
		else
			t[v] = min(t[2 * v] + mod2[2 * v], t[2 * v + 1] + mod2[2 * v + 1]);
	}
}

void upd(int v, int lk, int rk, int l, int r, int val)
{
	if (l > r)
		return;
	if (lk == l && rk == r)
	{
		//cerr << l << " " << r << " " << val << endl;
		t[v] = val;
		mod1[v] = val;
		mod2[v] = 0;
		modify(v);
		return;
	}
	push(v, lk, rk);
	int k = (lk + rk) / 2;
	upd(2 * v, lk, k, l, min(k, r), val);
	upd(2 * v + 1, k + 1, rk, max(k + 1, l), r, val);
}

void add(int v, int lk, int rk, int l, int r, int val)
{                                                     
	if (l > r)                                        
		return;                                       
	if (lk == l && rk == r)                           
	{                                          
		t[v] += val;
		mod2[v] += val;                                 
		modify(v);
		return;                                       
	}
	push(v, lk, rk);
	int k = (lk + rk) / 2;                            
	/*if (mod1[v])
	{
		upd(2 * v, lk, k, l, min(k, r), mod1[v]);            	
		upd(2 * v + 1, k + 1, rk, max(k + 1, l), r, mod1[v]);
		add(2 * v, lk, k, l, min(k, r), val + mod2[v]);            
		add(2 * v + 1, k + 1, rk, max(k + 1, l), r, val + mod2[v]);
		return;
	}*/
	add(2 * v, lk, k, l, min(k, r), val + mod2[v]);                  
	add(2 * v + 1, k + 1, rk, max(k + 1, l), r, val + mod2[v]);      
}
		
int main()
{
	std::ios_base::sync_with_stdio(0);
	freopen ("rmq2.in", "r", stdin);
	freopen ("rmq2.out", "w", stdout);
	int d;
	int l, r, x;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	sozd(1, 1, n);
	string s;
	while (cin >> s)
	{
		if (s == "min")
		{
			cin >> l >> r;
			d = searchmin(1, 1, n, l, r);
			cout << d << endl;
		}
		if (s == "set")
		{
			cin >> l >> r >> x;
			upd(1, 1, n, l, r, x);                 
		}
		if (s == "add")
		{
			cin >> l >> r >> x;
			add(1, 1, n, l, r, x);
		}
		for (int i = 1; i <= 3; i++)                                
			cerr << t[i] << " " << mod1[i] << " " << mod2[i] << endl;

		cerr << endl;
	}
	//for (int i = 1; i <= 10; i++)
	//	cerr << t[i] << " " << mod1[i] << " " << mod2[i] << endl;
	return 0;
}