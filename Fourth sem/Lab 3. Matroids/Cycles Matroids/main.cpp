#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

int n, m;
vector <pair <int, vector <int> > > cycles;
vector <pair <int,int> > w;
map <int, int> weight;
vector <int> ans;
// Есть циклы некоторого матроида => работает алгоритм Радо-Эдмондса. Если ни одно из подмножеств данного множества не является циклом, то множество независимо
// В итоге, жадно добавляем в наше множество элементы и проверяем, не стало ли какое-нибудь подмножество нашего множества циклом. Если стало, то выкидываем последний добавленный элемент, иначе продолжаем, оставив его

int main()
{
    freopen ("cycles.in", "r", stdin);
    freopen ("cycles.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int tmp;
        cin >> tmp;
        w.push_back(make_pair(tmp, i));
        weight.insert(make_pair(i, tmp));
    }
    sort(w.begin(), w.end());
    reverse(w.begin(), w.end());
    for (int i = 0; i < m; i++)
    {
        int tmp;
        cin >> tmp;
        vector <int> tmp_vec;
        for (int j = 0; j < tmp; j++)
        {
            int q;
            cin >> q;
            tmp_vec.push_back(q);
        }
        cycles.push_back(make_pair(tmp, tmp_vec));
    }
    sort(cycles.begin(), cycles.end());
    bool independent;
    for (int i = 0; i < w.size(); i++)
    {
        ans.push_back(w[i].second);
        independent = true;
        for (int j = 0; j < cycles.size(); j++)
        {
            if (cycles[j].first > ans.size())
            {
                break;
            }
            bool is[21] = {};
            for (int k = 0; k < cycles[j].first; k++)
            {
                is[cycles[j].second[k]] = true;
            }
            int number = 0;
            for (int k = 0; k < ans.size(); k++)
            {
                if (is[ans[k]])
                {
                    number++;
                }
            }
            if (number == cycles[j].first)
            {
                independent = false;
                break;
            }
        }
        if (!independent)
        {
            ans.pop_back();
        }
    }
    int sum = 0;
    for (int i = 0; i < ans.size(); i++)
    {
        sum += weight[ans[i]];
    }
    cout << sum << endl;
    return 0;
}