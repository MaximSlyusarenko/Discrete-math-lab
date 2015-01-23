
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
 
using namespace std;
 
struct tree
{
    int val;
    tree *l;
    tree *r;
};
 
int main()
{
    freopen ("bstsimple.in", "r", stdin);
    freopen ("bstsimple.out", "w", stdout);
    string s;
    int x;
    tree *root = NULL;
    while (cin >> s >> x)
    {
        if (s == "insert")
        {
            tree *tmp = root;
            bool flag = true;
            while (flag && tmp != NULL)
            {
                if (tmp -> val > x)
                {
                    if (tmp -> l == NULL)
                    {
                        tree *tmp1 = new tree;
                        tmp1 -> val = x;
                        tmp1 -> l = NULL;
                        tmp1 -> r = NULL;
                        tmp -> l = tmp1;
                        flag = false;
                    }
                    else
                        tmp = tmp -> l;
                }
                else if (tmp -> val < x)
                {
                    if (tmp -> r == NULL)   
                    {                       
                        tree *tmp1 = new tree;         
                        tmp1 -> val = x;    
                        tmp1 -> l = NULL;   
                        tmp1 -> r = NULL;   
                        tmp -> r = tmp1;    
                        flag = false;
                    }
                    else
                        tmp = tmp -> r;
                }
                else
                    flag = false;                      
            }
            if (tmp == NULL)
            {
                tree *tmp1 = new tree;
                tmp1 -> val = x;
                tmp1 -> l = NULL;
                tmp1 -> r = NULL;
                tmp = tmp1;
                root = tmp1;
            }
        }
        if (s == "exists")
        {
            tree *tmp = root;
            bool flag = true;
            while (tmp != NULL && flag)
            {
                if (tmp -> val > x)
                    tmp = tmp -> l;
                else if (tmp -> val < x)
                    tmp = tmp -> r;
                else
                {
                    cout << "true" << endl;
                    flag = false;
                }
            }
            if (flag)
            {
                cout << "false" << endl;
            }
        }
        if (s == "next")                            
        {                                           
            tree *tmp = root;                       
            int ans = 1000000010;                            
            while (tmp != NULL)                     
            {                                       
                if (tmp -> val <= x)                
                    tmp = tmp -> r;                 
                else                               
                {                                   
                    ans = tmp -> val;               
                    tmp = tmp -> l;                 
                }                                   
            }                                       
            if (ans == 1000000010)                           
                cout << "none" << endl;             
            else                                   
                cout << ans << endl;                
        }                                           
        if (s == "prev")                     
        {                                    
            tree *tmp = root;                
            int ans = -1000000010;
            while (tmp != NULL)
            {
                if (tmp -> val >= x)
                    tmp = tmp -> l;
                else
                {
                    ans = tmp -> val;
                    tmp = tmp -> r;
                }
            }
            if (ans == -1000000010)
                cout << "none" << endl;
            else
                cout << ans << endl;
        }
        if (s == "delete")
        {
            tree *tmp = root;
            tree *tmp1 = new tree;
            tree *tmp2 = new tree;
            int last;
            while (tmp != NULL && tmp -> val != x)
            {
                if (tmp -> val > x)
                {
                    tmp1 = tmp;
                    tmp = tmp -> l;
                    last = 0;
                }
                else if (tmp -> val < x)
                {
                    tmp1 = tmp;
                    tmp = tmp -> r;
                    last = 1;
                }
            }
            if (tmp != NULL)
            {
                tmp2 = tmp;
                if (tmp -> r == NULL && tmp -> l == NULL)
                {
                    if (last == 0)
                        tmp1 -> l = NULL;
                    else
                        tmp1 -> r = NULL;
                }
                else if (tmp -> r == NULL)
                {
                    tree *tmp3 = new tree;
                    tmp3 = tmp -> l;
                    if (tmp3 -> val > tmp1 -> val)
                        tmp1 -> r = tmp3;
                    else
                        tmp1 -> l = tmp3;
                }
                else if (tmp -> l == NULL)                  
                {                                          
                    tree *tmp3 = new tree;             
                    tmp3 = tmp -> r;                   
                    if (tmp3 -> val > tmp1 -> val)     
                        tmp1 -> r = tmp3;              
                    else                              
                        tmp1 -> l = tmp3;                                  
                }                                          
                else
                {
                    tree *tmp3 = new tree;
                    tmp3 = tmp;
                    tmp = tmp -> r;
                    while (tmp -> l != NULL)
                    {
                        tmp2 = tmp;
                        tmp = tmp -> l;
                    }
                    tmp3 -> val = tmp -> val;
                    tmp2 -> l = NULL;
                }
            }       
        }   
    }
    return 0;                                      
}