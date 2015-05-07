#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

int n;
vector <pair <int, int> > a;
set <int> available_time;

int main()
{
    freopen ("schedule.in", "r", stdin);
    freopen ("schedule.out", "w", stdout);
    cin >> n;
    long long sum = 0;
    int maxi = -1;
    for (int i = 0; i < n; i++)
    {
        int b, c;
        cin >> b >> c;
        sum += (long long) c;
        if (b > maxi)
        {
            maxi = b;
        }
        a.push_back(make_pair(c, b));
        available_time.insert(i + 1);
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    available_time.insert(-1);
    for (int i = 0; i < n; i++)
    {
        auto tmp = available_time.upper_bound(a[i].second);
        tmp--;
        if (*tmp == -1)
        {
            continue;
        }
        else
        {
            available_time.erase(tmp);
            sum -= a[i].first;
        }
    }
    cout << sum << endl;
    return 0;
}