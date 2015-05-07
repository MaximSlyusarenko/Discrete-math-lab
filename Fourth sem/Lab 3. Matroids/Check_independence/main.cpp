
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

set <pair <int, vector <int> > > different_sets;
vector <pair <int, vector <int> > > different;
int n, m;

vector <int> getdiff(vector <int> first, vector <int> second)
{
    vector <int> diff;
    if (second.size() == 0) // second.size() < first.size(), because of place from which function is called
    {
        return first;
    }
    bool is[11] = {};
    for (int i = 0; i < second.size(); i++)
    {
        is[second[i]] = true;
    }
    for (int i = 0; i < first.size(); i++)
    {
        if (!is[first[i]])
        {
            diff.push_back(first[i]);
        }
    }
    return diff;
}

int main()
{
    freopen ("check.in", "r", stdin);
    freopen ("check.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int c;
        vector <int> a;
        cin >> c;
        for (int j = 0; j < c; j++)
        {
            int tmp;
            cin >> tmp;
            a.push_back(tmp);
        }
        sort(a.begin(), a.end());
        if (different_sets.find(make_pair(c, a)) == different_sets.end())
        {
            different_sets.insert(make_pair(c, a));
        }
    }
    vector <int> empty;
    if (different_sets.find(make_pair(0, empty)) == different_sets.end()) // first axiom of matroid not performed
    {
        cout << "NO" << endl;
        return 0;
    }
    int factorials[11];
    factorials[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        factorials[i] = factorials[i - 1] * i;
    }
    for (auto it = different_sets.begin(); it != different_sets.end(); it++)
    {
        different.push_back(*it);
    }
    for (int i = 1; i < different.size(); i++)
    {
        int number_of_subsets[11] = {};
        for (int j = 1; j < i; j++)
        {
            vector <int> diff = getdiff(different[i].second, different[j].second);
            if (diff.size() == different[i].first - different[j].first)
            {
                number_of_subsets[different[j].first]++;
            }
        }
        for (int j = 1; j < different[i].first; j++)
        {
            if (number_of_subsets[j] != factorials[different[i].first] / factorials[j] / factorials[different[i].first - j]) // second axiom of matroid not performed. It exists set, all of which subsets not independence
            {
                cout << "NO" << endl;
                return 0;
            }
        }
    }
    vector <int> diff;
    vector <int> tmp;
    for (int i = 1; i < different.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (different[i].first > different[j].first)
            {
                diff = getdiff(different[i].second, different[j].second);
            }
            else
            {
                break;
            }
            tmp = different[j].second;
            bool ok = false;
            int pos = (int) tmp.size();
            for (int k = 0; k < diff.size(); k++)
            {
                tmp.push_back(diff[k]);
                int swaps = 0;
                while (pos != 0 && tmp[pos] < tmp[pos - 1])
                {
                    int t = tmp[pos];
                    tmp[pos] = tmp[pos - 1];
                    tmp[pos - 1] = t;
                    swaps++;
                    pos--;
                }
                if (different_sets.find(make_pair(tmp.size(), tmp)) != different_sets.end())
                {
                    ok = true;
                    break;
                }
                while (swaps > 0)
                {
                    int t = tmp[pos + 1];
                    tmp[pos + 1] = tmp[pos];
                    tmp[pos] = t;
                    swaps--;
                    pos++;
                }
                tmp.pop_back();
            }
            if (!ok) // third axiom of matroid not performed
            {
                cout << "NO" << endl;
                return 0;
            }
        }
    }
    cout << "YES" << endl; // all axioms performed
    return 0;
}