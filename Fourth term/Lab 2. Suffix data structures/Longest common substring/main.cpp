#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

string s, t;
int n, m, common_size;

int p[500000], lcp[500000], c[500000], cnew[500000], pnew[500000], cnt[500000], pos[500000];

void build_suffix_array()
{
    s += 'a' - 2;
    for (int i = 0; i < s.size(); i++)
    {

        cnt[s[i] - 'a' + 2]++;
    }
    for (int i = 1; i < 29; i++)
    {
        cnt[i] += cnt[i - 1];
    }
    for (int i = 0; i < s.size(); i++)
    {
        p[--cnt[s[i] - 'a' + 2]] = i;
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
}

void build_lcp()
{
    int length = (int) s.size();
    for (int i = 0; i < length; i++)
    {
        pos[p[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < length; i++)
    {
        if (k > 0)
        {
            k--;
        }
        if (pos[i] == length - 1)
        {
            lcp[length - 1] = 0;
            k = 0;
        }
        else
        {
            int j = p[pos[i] + 1];
            while (max(i, j) < length - k && s[i + k] == s[j + k])
            {
                k++;
            }
            lcp[pos[i]] = k;
        }
    }
}

int main()
{
    freopen ("common.in", "r", stdin);
    freopen ("common.out", "w", stdout);
    cin >> s >> t;
    n = (int) s.size();
    m = (int) t.size();
    char c = 'a' - 1;
    s += c;
    s += t;
    common_size = (int) s.size() + 1;
    build_suffix_array();
    build_lcp();
    int maximum = -1;
    // lcp[i] = lcp[i - 1] for every i
    int tmp2 = lcp[0];
    for (int i = 1; i < common_size; i++)
    {
        int tmp1 = tmp2;
        tmp2 = lcp[i];
        lcp[i] = tmp1;
    }
    for (int i = 1; i < common_size; i++)
    {
        int tmp = 0;
        if (p[i] < n && p[i - 1] > n)
        {
            tmp = min(lcp[i], n - p[i]);
        }
        if (p[i] > n && p[i - 1] < n)
        {
            tmp = max(tmp , min(lcp[i], n - p[i - 1]));
        }
        maximum = max(maximum, tmp);
    }
    string ans;
    for (int i = 1; i < common_size; i++)
    {
        int tmp = 0;
        if (p[i] < n && p[i - 1] > n)
        {
            tmp = min(lcp[i], n - p[i]);
        }
        if (p[i] > n && p[i - 1] < n)
        {
            tmp = max(tmp , min(lcp[i], n - p[i - 1]));
        }
        if (tmp == maximum)
        {
            ans = s.substr((unsigned long) p[i], (unsigned long) tmp);
            break;
        }
    }
    cout << ans << endl;
    return 0;
}