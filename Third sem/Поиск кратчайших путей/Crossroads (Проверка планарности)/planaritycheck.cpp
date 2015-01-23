#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <fstream>
#include <stdexcept>

using namespace std;

bool full_bipartite, used[10];
int t, n, deg[10], col[10], g[10][10], c[10];
vector <string> K33, a;

void dfs(int v, int color, int parent)   
{
	used[v] = true;                      
	c[v] = color;                        
	color++;                             
	color %= 2;                          
	for (int i = 1; i <= 6; i++)
	{                                    
		if (g[v][i] && i == parent)           
		{                                
			continue;                    
		}                                
		if (!used[i] && g[v][i] == 1)
		{                                
			dfs(i, color, v);      
		}                                
		else if (g[v][i] == 1)                            
		{                                
			if (color != c[i])     
			{                            
				full_bipartite = false;       
			}                            
		}                                
	}                                    
}                                        

void gen(string s)                 
{                                  
	if (s.size() == 15)
	{
		a.push_back(s);            
	}
	else                           
	{                              
		string s1 = s + "0";       
		gen(s1);                   
		string s2 = s + "1";   
		gen(s2);               
	}                              
}					               

int main()
{
	freopen ("planaritycheck.in", "r", stdin);
	freopen ("planaritycheck.out", "w", stdout);
	gen("");
	for (int i = 0; i < a.size(); i++)
	{   
		full_bipartite = true;
		int n = 6;
		for (int j = 1; j <= n; j++)
		{
			deg[j] = 0;
			for (int k = 1; k <= n; k++)
			{
				g[j][k] = 0;
			}
		}
		int r = 0;
		for (int j = 2; j <= n; j++)   
		{                              
			for (int k = 1; k < j; k++)
			{                          
				if (a[i][r] == '1')       
				{                      
					g[j][k] = 1;       
					g[k][j] = 1;       
					deg[j]++;          
					deg[k]++;          
				}                      
				r++;                   
			}                          
		}
		for (int j = 1; j <= n; j++)
		{
			if (deg[j] != 3)
			{
				full_bipartite = false;
			}
		}
		for (int j = 1; j <= n; j++)
		{
			used[j] = false;
			c[j] = -1;
		}
		for (int j = 1; j <= n; j++)
		{
			if (!used[j])
			{
				dfs(j, 0, -1);
			}
		}
		if (full_bipartite)
		{              
			K33.push_back(a[i]);
		}
	}
	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		for (int j = 1; j <= 6; j++)
		{
			deg[j] = 0;
			for (int k = 1; k <= 6; k++)
			{
				g[j][k] = 0;
			}
		}
		string s;
		int k;
		cin >> s;
		if (s.size() < 10)
		{
			cout << "YES" << endl;
			continue;
		}
		else if (s.size() == 10)
		{
			n = 5;
		}
		else
		{
			n = 6;
		}
		int r = 0;
		for (int i = 2; i <= n; i++)
		{
			for (int j = 1; j < i; j++)
			{
				if (s[r] == '1')
				{
					g[i][j] = 1;
					g[j][i] = 1;
					deg[i]++;
					deg[j]++;
				}
				r++;
			}
		}
		if (n == 6) // K33. Вектор К33- К33 графы со всеми возможными нумерациями вершин. Если в графе из К33 есть ребро, а в нашем графе там ребра нет, то нет подграфа нашего графа, совпадающего с данным графом из К33. Иначе, такой подграф есть и наш граф не является планарным
		{
			bool flag1;
			for (int i = 0; i < K33.size(); i++)
			{
				flag1 = true;
				string tmp = K33[i];
				for (int j = 0; j < s.size(); j++)
				{
					if (tmp[j] == '1' && s[j] != '1')
					{
						flag1 = false;
					}
				}
				if (flag1)
				{
					break;
				}
			}
			if (flag1)
			{
				cout << "NO" << endl;
				continue;
			}
		}
		if (n == 5)      // K5. Если 5 вершин, то он не планарен только, если является K5
		{
			k = 0;
			for (int i = 1; i <= n; i++)
			{
				if (deg[i] >= 4)
				{
					k++;
				}
			}
			if (k == 5)
			{	
				cout << "NO" << endl;
				continue;
			}
		}
		if (n == 6) // Если 6 вершин, то возможны случаи, когда он при удалении вершины с минимальной степенью остается K5 или, если эта вершина соединена только с двумя и эти две не соединены между собой, то при ее удалении тоже может остаться К5. Если оба варианта не выполнены, то нет подграфа, гомеоморфного К5
		{
			int mini = 100;
			int q;
			for (int i = 1; i <= n; i++)
			{
				if (deg[i] < mini)
				{
					mini = deg[i];
					q = i;
				}
			}
			int d[10];
			for (int i = 1; i <= n; i++)
			{
				d[i] = deg[i];
			}
			sort(d + 1, d + n + 1);
			int k = d[2];
			if (k >= 5)
			{
				cout << "NO" << endl;
				continue;
			}
			if (k <= 3)
			{
				cout << "YES" << endl;
				continue;
			}
			int h = 0;
			for (int i = 1; i <= n; i++)
			{
				if (deg[i] == 4 && i != q && g[i][q] == 1)
				{
					h++;
				}
			}
			if (h == 0)
			{
				cout << "NO" << endl;
				continue;
			}
			if (h == 2)
			{
				int p[10], z = 0;
				for (int i = 1; i <= n; i++)
				{
					if (deg[i] == 4 && i != q && g[i][q] == 1)
					{
						p[z] = i;
						z++;
					}
				}
				if (g[p[0]][p[1]] == 0)
				{
					cout << "NO" << endl;
					continue;
				}
			}
		}
		cout << "YES" << endl;
	}				 		
	return 0;
}