#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
 
#define inf (int)(3e9)
 
using namespace std;
 
int a[200000], o1[200000], o2[200000];
int size;
 
void totalSwap(int v1, int v2)
{
        int tmp = a[v1];
        a[v1] = a[v2];
        a[v2] = tmp;
 
        tmp = o2[v1];
        o2[v1] = o2[v2];
        o2[v2] = tmp;
 
    o1[o2[v1]] = v1;
    o1[o2[v2]] = v2;
}
 
void siftUp(int v)
{
        if (v == 1)
                return;
 
        if (a[v] < a[v / 2])
        {
                totalSwap(v, v / 2);
                siftUp(v / 2);
        }      
}
 
void siftDown(int v)
{
        int l = inf;
        int r = inf;
 
        if (2 * v <= size)
                l = a[2 * v];
 
        if (2 * v + 1 <= size)
                r = a[2 * v + 1];
 
        if (l == inf && r == inf)
                return;
 
        if (l < r)
        {
                if (a[v] > l)
                {
                        totalSwap(v, 2 * v);
                        siftDown(2 * v);
                }
        }
        else
        {
                if (a[v] > r)
                {
                        totalSwap(v, 2 * v + 1);
                        siftDown(2 * v + 1);
                }
        }
}
 
bool isEmpty()
{
        return size == 0;
}
 
void push(int val, int num)
{
        size++;
    a[size] = val;
    o1[num] = size;
    o2[size] = num;
    siftUp(size);
}
 
void pop()
{
        if (isEmpty())
                cout << "*" << endl;
        else
        {
        cout << a[1] << endl;
        if (!isEmpty())
        {
                a[1] = a[size];
                o1[o2[size]] = 1;
                o2[1] = o2[size];
                size--;
                siftDown(1);
        }
    }
}
 
void decrease(int num, int val)
{
        a[o1[num]] = val;
        siftUp(o1[num]);       
}
 
void print()
{
        cerr << "a: ";
        for (int i = 1; i <= size; i++)
                cerr << a[i] << " ";
        cerr << endl;
        cerr << "o1: ";
        for (int i = 1; i <= size; i++)
                cerr << o1[i] << " ";
        cerr << endl;
        cerr << "o2: ";
        for (int i = 1; i <= size; i++)
                cerr << o2[i] << " ";
        cerr << endl;
        cerr << endl;
}
 
int main()
{
    freopen("priorityqueue.in", "r", stdin);
    freopen("priorityqueue1.out", "w", stdout);
 
    string s;
    int num, val;
    int cnt = 0;    
    while (cin >> s)
    {
        //if (cnt == 10)
        //      return 0;
        cnt++;
        if (s[0] == 'p')
        {
                cin >> val;
                push(val, cnt);
                //cerr << s << " " << val << endl;
        }
        if (s[0] == 'e')
        {
                pop();
                //cerr << s << endl;
        }
        if (s[0] == 'd')
        {
                cin >> num >> val;
                decrease(num, val);
                //cerr << s << " " << val << " " << num << endl;
        }
       
        //print();
    }
 
        return 0;
}