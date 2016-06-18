
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <fstream>
  
using namespace std;
  
struct mylist {
    string key;
    string value;
    mylist *prev;
    mylist *next;
};
  
mylist *a[21000][700];
long long h[200000], h1[200000];
string p[200000], b[200000], t[200000], c[200000];
  
int main()
{
    ifstream in ("multimap.in");
    ofstream out ("multimap.out");
    int n = 20011;
    int n1 = 503;
    string s;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n1; j++)
            a[i][j] = NULL;
    int i = 0;
    while (in >> b[i])
    {
        if (b[i] == "put")
        {
            in >> t[i] >> p[i];
            long long q = 3;
            for (int j = 0; j < t[i].size(); j++)
            {
                h[i] += (int(t[i][j]) - int('a')) * q;
                h[i] %= n;
                q *= 3;
            }
            q = 3;
            for (int j = 0; j < p[i].size(); j++)
            {
                h1[i] += (int(p[i][j]) - int('a')) * q;
                h1[i] %= n1;
                q *= 3;
            }
        }
        if (b[i] == "delete")
        {
            in >> t[i] >> p[i];
            long long q = 3;                       
            for (int j = 0; j < t[i].size(); j++)     
            {                                      
                h[i] += (int(t[i][j]) - int('a')) * q;
                h[i] %= n;                         
                q *= 3;                            
            }
            q = 3;
            for (int j = 0; j < p[i].size(); j++)      
            {                                          
                h1[i] += (int(p[i][j]) - int('a')) * q;
                h1[i] %= n1;                           
                q *= 3;                                
            }                                          
        }
        if (b[i] == "get")
        {
            in >> t[i];
            long long q = 3;                       
            for (int j = 0; j < t[i].size(); j++)     
            {                                      
                h[i] += (int(t[i][j]) - int('a')) * q;
                h[i] %= n;                         
                q *= 3;                            
            }
        }
        if (b[i] == "deleteall")
        {
            in >> t[i];
            long long q = 3;                          
            for (int j = 0; j < t[i].size(); j++)     
            {                                         
                h[i] += (int(t[i][j]) - int('a')) * q;
                h[i] %= n;                            
                q *= 3;                               
            }                                         
        }
        i++;
    }
    for (int j = 0; j < i; j++)
    {
        if (b[j] == "put")
        {
            if (a[h[j]][h1[j]] == NULL)
            {
                mylist *tmp = new mylist;
                tmp -> key = t[j];
                tmp -> value = p[j];
                tmp -> next = NULL;
                tmp -> prev = NULL;
                a[h[j]][h1[j]] = tmp;
            }
            else
            {                   
                mylist *tmp = a[h[j]][h1[j]];  
                while (tmp -> next != NULL && (tmp -> key != t[j] || tmp -> value != p[j]))
                    tmp = tmp -> next;
                bool flag = true;
                if (tmp -> key == t[j] && tmp -> value == p[j])
                {
                    flag = false;
                }
                if (flag)
                {
                    mylist *tmp1 = new mylist;
                    tmp1 -> key = t[j];
                    tmp1 -> value = p[j];
                    tmp1 -> next = NULL;
                    tmp1 -> prev = tmp;
                    tmp -> next = tmp1;
                }
            }
        }
        if (b[j] == "delete")
        {                          
            if (a[h[j]][h1[j]] != NULL)
            {
                mylist *tmp = a[h[j]][h1[j]];
                while (tmp != NULL && (tmp -> key != t[j] || tmp -> value != p[j]))
                    tmp = tmp -> next;
                if (tmp != NULL)
                {
                    mylist *tmp1 = tmp -> prev;
                    mylist *tmp2 = tmp -> next;
                    if (tmp1 == NULL)
                    {
                        if (tmp2 != NULL)
                            tmp2 -> prev = NULL;
                        a[h[j]][h1[j]] = tmp2;
                    }
                    else
                    {
                        if (tmp2 == NULL)
                        {
                            tmp1 -> next = NULL;
                        }
                        else
                        {
                            tmp1 -> next = tmp2;
                            tmp2 -> prev = tmp1;
                        }
                    }
                }
            }
        }
        if (b[j] == "get")
        {
            int q = 0;
            for (int k = 0; k < n1; k++)
            {
                if (a[h[j]][k] != NULL)
                {
                    mylist *tmp = a[h[j]][k];
                    while (tmp != NULL)
                    {
                        while (tmp != NULL && tmp -> key != t[j])
                            tmp = tmp -> next;
                        if (tmp != NULL) 
                        {
                            c[q] = tmp -> value;
                            q++;
                            tmp = tmp -> next;
                        }
                    }
                }
            }
            if (q == 0)
            {
                out << 0 << endl;
            }
            else
            {
                out << q << " ";
                for (int i = 0; i < q; i++)
                    out << c[i] << " ";
                out << endl;
            }
        }
        if (b[j] == "deleteall")                                                       
        {
            for (int k = 0; k < n1; k++)                                                                        
            {
                if (a[h[j]][k] != NULL)                                                    
                {                                                                       
                    mylist *tmp = a[h[j]][k];                                              
                    while (tmp != NULL)
                    {
                        while (tmp != NULL && tmp -> key != t[j]) 
                            tmp = tmp -> next;                                              
                        if (tmp != NULL)                                                    
                        {                                                                   
                            mylist *tmp1 = tmp -> prev;                                     
                            mylist *tmp2 = tmp -> next;                                     
                            if (tmp1 == NULL)                                               
                            {                                                               
                                if (tmp2 != NULL)                                           
                                    tmp2 -> prev = NULL;                                    
                                a[h[j]][k] = tmp2;                                             
                            }                                                               
                            else                                                          
                            {                                                               
                                if (tmp2 == NULL)                                           
                                {                                                           
                                    tmp1 -> next = NULL;                                    
                                }                                                           
                                else                                                      
                                {                                                           
                                    tmp1 -> next = tmp2;                                    
                                    tmp2 -> prev = tmp1;                                    
                                }                                                           
                            }
                            tmp = tmp -> next;                                                               
                        }                                                                   
                    }
                }
            }                                                                             
        }
    }                                                                              
    return 0;
}