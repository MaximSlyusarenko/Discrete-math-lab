
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
 
using namespace std;
 
int n, k;
string a[2000], b[2000];
 
void merge_sort(int l, int r, int ind)
{
    if (r - l < 1)
        return;
    int m = (l + r) / 2;
    merge_sort(l, m, ind);
    merge_sort(m + 1, r, ind);
    int i = l, j = m + 1;
    int q = 0;
    while (i <= m || j <= r)
    {
        if (j > r)
        {
            b[q] = a[i];
            i++;
        }
        else if (i > m)
        {
            b[q] = a[j];
            j++;
        }
        else if (a[i][ind] <= a[j][ind])
        {
            b[q] = a[i];
            i++;
        }
        else
        {
            b[q] = a[j];        
            j++;
        }
        q++;
    }
    for (int i = 0; i < q; i++)
    {
        a[l + i] = b[i];
    }
}
 
int main()
{
    freopen("radixsort.in", "r", stdin);
    freopen("radixsort.out", "w", stdout);
    int m;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < k; i++)
    {
        merge_sort(0, n - 1, m - i - 1);    
    }
    for (int i = 0; i < n; i++)
        cout << a[i] << endl;
    return 0;
}