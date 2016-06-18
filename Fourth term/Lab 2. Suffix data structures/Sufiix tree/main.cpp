#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

string s;
pair <int, int> ptr = make_pair(0, 0);

struct node
{
    int left;
    int right;
    int parent;
    int link;
    map <char, int> next;
    int size()
    {
        return right - left;
    }
    node (int left = 0, int right = 0, int parent = -1): left(left), right(right), parent(parent), link(-1) {}
};

vector <node> tree;

pair <int, int> go(pair <int, int> st, int l, int r)
{
    while (l < r)
    {
        if (st.second == tree[st.first].size())
        {
            if (tree[st.first].next.find(s[l]) == tree[st.first].next.end())
            {
                tree[st.first].next.insert(make_pair(s[l], -1));
            }
            st = make_pair(tree[st.first].next[s[l]], 0);
            if (st.first == -1)
            {
                return st;
            }
        }
        else
        {
            if (s[tree[st.first].left + st.second] != s[l])
            {
                return make_pair(-1, -1);
            }
            if ((r - l) < tree[st.first].size() - st.second)
            {
                return make_pair(st.first, st.second + r - l);
            }
            l += tree[st.first].size() - st.second;
            st.second = tree[st.first].size();
        }
    }
    return st;
}

int split(pair <int, int> state)
{
    if (state.second == tree[state.first].size())
    {
        return state.first;
    }
    if (state.second == 0)
    {
        return tree[state.first].parent;
    }
    node tmp = tree[state.first];
    tree.push_back(node(tmp.left, tmp.left + state.second, tmp.parent));
    tree[tmp.parent].next[s[tmp.left]] = (int) tree.size() - 1;
    tree[tree.size() - 1].next[s[tmp.left + state.second]] = state.first;
    tree[state.first].parent = (int) (tree.size() - 1);
    tree[state.first].left += state.second;
    return (int) (tree.size() - 1);
}

int get_link(int vertex)
{
    if (tree[vertex].link != -1)
    {
        return tree[vertex].link;
    }
    if (tree[vertex].parent == -1)
    {
        return 0;
    }
    int to = get_link(tree[vertex].parent);
    int add = 0;
    if (tree[vertex].parent == 0)
    {
        add++;
    }
    pair <int, int> tmp = go(make_pair(to, tree[to].size()), tree[vertex].left + add, tree[vertex].right);
    int l = split(tmp);
    tree[vertex].link = l;
    return tree[vertex].link;
}

int main()
{
    freopen ("tree.in", "r", stdin);
    freopen ("tree.out", "w", stdout);
    cin >> s;
    tree.push_back(node(0, 0, -1));
    for (int i = 0; i < s.size(); i++)
    {
        while (true)
        {
            pair <int, int> new_ptr = go(ptr, i, i + 1);
            if (new_ptr.first != -1)
            {
                ptr = new_ptr;
                break;
            }
            int mid = split(ptr);
            tree.push_back(node(i, (int) s.size(), mid));
            tree[mid].next[s[i]] = (int) (tree.size() - 1);
            ptr.first = get_link(mid);
            ptr.second = tree[ptr.first].size();
            if (mid == 0)
            {
                break;
            }
        }
    }
    cout << tree.size() << " " << tree.size() - 1 << endl;
    vector <pair <int, pair <int, pair <int, int> > > > ans;
    for (int i = 1; i < tree.size(); i++)
    {
        ans.push_back(make_pair(tree[i].parent + 1, make_pair(i + 1, make_pair(tree[i].left + 1, tree[i].right))));
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i].first << " " << ans[i].second.first << " " << ans[i].second.second.first << " " << ans[i].second.second.second << endl;
    }
    return 0;
}