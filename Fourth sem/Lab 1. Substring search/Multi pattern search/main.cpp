#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

struct node
{
    node* son[26];
    node* go[26];
    node* parent;
    node* suff_link;
    node* compressed;
    char char_to_parent;
    bool terminate;
    vector <int> pattern_numbers;
};

node* get_suffix_link(node* t);

node* root;
int n;
string text;
bool found[2000000];

node* get_go(node* t, char c)
{
    if (t -> go[c] == NULL)
    {
        if (t -> son[c] != NULL)
        {
            t -> go[c] = t -> son[c];
        }
        else
        {
            if (t == root)
            {
                t -> go[c] = root;
            }
            else
            {
                t -> go[c] = get_go(get_suffix_link(t), c);
            }
        }
    }
    return t -> go[c];
}

node* get_suffix_link(node* t)
{
    if (t -> suff_link == NULL)
    {
        if (t == root || t -> parent == root)
        {
            t -> suff_link = root;
        }
        else
        {
            t -> suff_link = get_go(get_suffix_link(t -> parent), t -> char_to_parent);
        }
    }
    return t -> suff_link;
}

node* get_compressed(node* t)
{
    if (t -> compressed == NULL)
    {
        node* link = get_suffix_link(t);
        if (link -> terminate)
        {
            t -> compressed = link;
        }
        else if (link == root)
        {
            t -> compressed = root;
        }
        else
        {
            t -> compressed = get_compressed(link);
        }
    }
    return t -> compressed;
}

void add_to_trie(string s, int number)
{
    node* cur = root;
    for (int i = 0; i < s.size(); i++)
    {
        char c = s[i] - 'a';
        if (cur -> son[c] == NULL)
        {
            cur -> son[c] = new node;
            memset(cur -> son[c] -> son, NULL, sizeof(cur -> son[c] -> son));
            memset(cur -> son[c] -> go, NULL, sizeof(cur -> son[c] -> go));
            cur -> son[c] -> suff_link = NULL;
            cur -> son[c] -> compressed = NULL;
            cur -> son[c] -> parent = cur;
            cur -> son[c] -> char_to_parent = c;
            cur -> son[c] -> terminate = false;
        }
        cur = cur -> son[c];
    }
    cur -> terminate = true;
    cur -> pattern_numbers.push_back(number);
}

int main()
{
    freopen("search4.in", "r", stdin);
    freopen("search4.out", "w", stdout);
    root = new node;
    memset(root -> son, NULL, sizeof(root -> son));
    memset(root -> go, NULL, sizeof(root -> go));
    root -> suff_link = NULL;
    root -> compressed = NULL;
    root -> parent = NULL;
    root -> terminate = false;
    scanf("%d\n", &n);
    char tmp[2000000];
    for (int i = 0; i < n; i++)
    {
        scanf("%s\n", tmp);
        string stmp = (const char*) tmp;
        add_to_trie(stmp, i);
    }
    scanf("%s\n", tmp);
    text = (const char*) tmp;
    node* cur = root;
    bool was;
    for (int j = 0; j < text.size(); j++)
    {
        char c = text[j] - 'a';
        cur = get_go(cur, c);
        was = false;
        for (node* v = cur; v != root; v = get_compressed(v))
        {
            for (int i = 0; i < v -> pattern_numbers.size(); i++)
            {
                if (found[v -> pattern_numbers[i]])
                {
                    was = true;
                    break;
                }
                else
                {
                    found[v -> pattern_numbers[i]] = true;
                }
            }
            if (was)
            {
                break;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (found[i])
        {
            printf("%s\n", "YES");
        }
        else
        {
            printf("%s\n", "NO");
        }
    }
    return 0;
}