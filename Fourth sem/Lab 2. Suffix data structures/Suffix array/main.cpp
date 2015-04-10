#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>

using namespace std;

string s;
int p[500000], c[500000], pnew[500000], cnew[500000], cnt[500000];

int main()
{
    freopen ("array.in", "r", stdin);
    freopen ("array.out", "w", stdout);
    cin >> s;
    s += 'a' - 1;
    for (int i = 0; i < s.size(); i++)
    {

        cnt[s[i] - 'a' + 1]++;
    }
    for (int i = 1; i < 29; i++)
    {
        cnt[i] += cnt[i - 1];
    }
    for (int i = 0; i < s.size(); i++)
    {
        p[--cnt[s[i] - 'a' + 1]] = i;
    }
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < s.size(); i++)
    {
        if (s[p[i]] != s[p[i - 1]])
        {
            classes++;
        }
        c[p[i]] = classes - 1;
    }
    for (int i = 0; (1 << i) < s.size(); i++)
    {
        for (int j = 0; j < s.size(); j++)
        {
            pnew[j] = p[j] - (1 << i);
            if (pnew[j] < 0)
            {
                pnew[j] += s.size();
            }
        }
        for (int j = 0; j < s.size(); j++)
        {
            cnt[j] = 0;
        }
        for (int j = 0; j < s.size(); j++)
        {
            cnt[c[pnew[j]]]++;
        }
        for (int j = 1; j < classes; j++)
        {
            cnt[j] += cnt[j - 1];
        }
        for (int j = (int) (s.size() - 1); j >= 0; j--)
        {
            p[--cnt[c[pnew[j]]]] = pnew[j];
        }
        cnew[p[0]] = 0;
        classes = 1;
        for (int j = 1; j < s.size(); j++)
        {
            int length = (int) s.size();
            int mid = (p[j] + (1 << i)) % length;
            int mid1 = (p[j - 1] + (1 << i)) % length;
            if (c[p[j]] != c[p[j - 1]] || c[mid] != c[mid1])
            {
                classes++;
            }
            cnew[p[j]] = classes - 1;
        }
        for (int j = 0; j < s.size(); j++)
        {
            c[j] = cnew[j];
        }
    }
    for (int i = 1; i < s.size(); i++)
    {
        cout << p[i] + 1 << " ";
    }
    return 0;
}