#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

struct node;
int n, m;
int a[200000];
string s;
pair <int, int> ptr = make_pair(0, 0);
vector <node> tree;
vector <vector <int> > graph;
vector <long long> leafs;
vector <bool> used;
long long max_ans = -1;
long long refrain_length = 0;
long long to_symbol = -1;

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

void build_suffix_tree()
{
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
}

void build_graph()
{
    used.resize(tree.size() + 100);
    graph.resize(tree.size() + 100);
    leafs.reserve(tree.size() + 100);
    for (int i = 1; i < tree.size(); i++)
    {
        graph[tree[i].parent].push_back(i);
    }
}

void dfs(int v, long long cur_length)
{
    if (graph[v].size() == 0)
    {
        used[v] = true;
        leafs[v] = 1;
        if (leafs[v] * (cur_length - 1) > max_ans) // if it's leaf then last symbol = 'a' - 1, it's why here is current_length - 1
        {
            max_ans = leafs[v] * (cur_length - 1);
            refrain_length = cur_length - 1;
            to_symbol = tree[v].right - 1;
        }
        return;
    }
    used[v] = true;
    long long leafs_in_subtree = 0;
    for (int i = 0; i < graph[v].size(); i++)
    {
        if (!used[graph[v][i]])
        {
            dfs(graph[v][i], cur_length + (long long) tree[graph[v][i]].right - (long long) tree[graph[v][i]].left);
        }
        leafs_in_subtree += leafs[graph[v][i]];
    }
    leafs[v] = leafs_in_subtree;
    if (leafs[v] * cur_length >= max_ans)
    {
        max_ans = leafs[v] * cur_length;
        refrain_length = cur_length;
        to_symbol = tree[v].right;
    }
}

int main()
{
    freopen ("refrain.in", "r", stdin);
    freopen ("refrain.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        char c = (char) a[i];
        c += 'a' - 1;
        s += c;
    }
    char c = 'a' - 1;
    s += c;
    build_suffix_tree();
    build_graph();
    dfs(0, 0);
    cout << max_ans << endl << refrain_length << endl;
    for (int i = (int) (to_symbol - refrain_length); i < to_symbol; i++)
    {
        char d = s[i];
        d -= 'a';
        int tmp = (int) d;
        tmp++;
        cout << tmp << " ";
    }
    return 0;
}