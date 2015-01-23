#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
 
using namespace std;
 
string s;
int a[200000];
int b[200000], op[200000];
 
int main()
{
    freopen ("priorityqueue.in", "r", stdin);
    freopen ("priorityqueue.out", "w", stdout);
    int j = 0;
    int size = 0, inf = 1000000001;
    //b - где находится число, добавленное на j-ой операции 
    while (cin >> s)
    {
        j++;
        if (s == "push")
        {
            int p;
            cin >> p;
            size++;
            a[size] = p;
            int i = size;
            while (i > 1 && p < a[i / 2])
            {
                a[i] = a[i / 2];
                b[op[i / 2]] = i;
                op[i] = op[i / 2];
                i /= 2;
            }
            a[i] = p;
            b[j] = i;
            op[i] = j;
        }
        if (s == "extract-min")
        {
            if (size == 0)
                cout << "*" << endl;
            else
            {
                cout << a[1] << endl;
                int t = a[size];
                a[1] = t;
                a[size] = inf;
                op[1] = op[size];
                b[op[1]] = 1;
                int q = op[1];
                size--;
                int i = 1;
                while (2 * i <= size && (t > a[2 * i] || t > a[2 * i + 1]))
                {
                    if ((2 * i + 1 > size) || (a[2 * i] < a[2 * i + 1]))
                    {
                        a[i] = a[2 * i];
                        b[op[2 * i]] = i;
                        op[i] = op[2 * i];
                        i *= 2;
                    }
                    else
                    {
                        a[i] = a[2 * i + 1];
                        b[op[2 * i + 1]] = i;
                        op[i] = op[2 * i + 1];
                        i = 2 * i + 1;
                    }
                }
                a[i] = t;
                b[q] = i;
                op[i] = q;
            }
        }
        if (s == "decrease-key")
        {
            int k, l;
            cin >> k >> l;
            a[b[k]] = l;
            int i = b[k];
            while (i > 1 && l < a[i / 2])          
            {                                   
                a[i] = a[i / 2];                
                b[op[i / 2]] = i;               
                op[i] = op[i / 2];              
                i /= 2;                         
            }
            a[i] = l;  
            b[k] = i;  
            op[i] = k;
        }                    
    }
    return 0;
}