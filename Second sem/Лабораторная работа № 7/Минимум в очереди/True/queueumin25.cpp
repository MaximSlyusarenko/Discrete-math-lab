
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
 
using namespace std;
 
long long n, size1 = 10, tmp1 = 0, tmp2 = 0, size2 = 10, cons, m, k, a, b, c, x[2000];
pair <int, int> s1[16000001];
pair <int, int> s[16000001];
 
int pop12()                  
{                           
    tmp1--;                 
    return s1[tmp1].first;  
}                           
 
void push21(int k)                                      
{                                                      
    s[tmp2].first = k;                                 
    if (tmp2 == 0)                                     
        s[tmp2].second = k;                            
    else                                              
        s[tmp2].second = min(k, s[tmp2 - 1].second);   
    tmp2++;                                            
}                                                      
 
void push1(int k)
{                                                                                 
    s1[tmp1].first = k;
    if (tmp1 == 0)
        s1[tmp1].second = k;
    else
        s1[tmp1].second = min(k, s1[tmp1 - 1].second);                                      
    tmp1++;
    if (tmp1 >= 15500000)
    {
        long long f = tmp1;
        for (int i = 0; i < f; i++)
        {
            int p = pop12();
            push21(p);
        }
    }                                         
}                                                     
 
int pop1()
{
    tmp1--;
    return s1[tmp1].first;
}
 
void push2(int k)                                                   
{                                                                                                                   
    s[tmp2].first = k;
    if (tmp2 == 0)
        s[tmp2].second = k;
    else                                     
        s[tmp2].second = min(k, s[tmp2 - 1].second);                    
    tmp2++;                                                          
}                                                                   
 
void pop2()
{
    if (tmp2 == 0)
    {
        long long f = tmp1;
        for (int i = 0; i < f; i++)
        {
            int p = pop1();
            push2(p);
        }
    }
    tmp2--;
}               
 
int main()
{
    freopen ("queuemin2.in", "r", stdin);
    freopen ("queuemin2.out", "w", stdout);
    cin >> n >> m >> k >> a >> b >> c;
    for (int i = 1; i <= k; i++)
    {
        cin >> x[i];
    }
    cons = 1;
    long long h;
    for (int i = 1; i <= 32; i++)
    {
        cons *= 2;
        if (i == 31)
            h = cons;
    }
    long long l = h - 1, v = -h, sum = 0;
    for (int i = 1; i <= n; i++)
    {
        long long q;
        if (i <= k)
            q = x[i];
        else
        {
            long long d;
            if (tmp1 >= 2)
                d = a * s1[tmp1 - 2].first + b * s1[tmp1 - 1].first + c;
            else if (tmp1 == 1)
                d = a * s[0].first + b * s1[0].first + c;
            else
                d = b * s[0].first + a * s[1].first + c;
            //q = d % cons;
            q = (d << 32) >> 32;
            if (q > l)
                q -= cons;
            if (q < v)
                q += cons;
        }
        if (i >= m)
        {
            push1(q);
            if (tmp2 == 0)
                sum += s1[tmp1 - 1].second;
            else
                sum += min(s1[tmp1 - 1].second, s[tmp2 - 1].second);
            pop2();
        }
        else
            push1(q);
    }
    cout << sum;
    return 0;
}