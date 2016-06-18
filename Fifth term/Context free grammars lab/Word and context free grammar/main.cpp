#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stdio.h>
#include <cstring>

using namespace std;

const int minimal_unterminal = 'z' + 1;
int m;
int start;
set <pair <int, vector <int> > > set_rules;
map <int, int> letter_to_unterminal;
int current_unterminal = 'z' + 1;

vector <pair <int, vector <int> > > set_to_vec(set <pair <int, vector <int> > > set1)
{
    vector <pair <int, vector <int> > > ans;
    for (auto it = set1.begin(); it != set1.end(); it++)
    {
        ans.push_back(*it);
    }
    return ans;
}

set <pair <int, vector <int> > > vec_to_set(vector <pair <int, vector <int> > > vec)
{
    set <pair <int, vector <int> > > ans;
    for (int i = 0; i < vec.size(); i++)
    {
        ans.insert(vec[i]);
    }
    return ans;
}

set <pair <int, vector <int> > > remove_long_rules()
{
    vector <pair <int, vector <int> > > rules_without_long;
    vector <pair <int, vector <int> > > rules = set_to_vec(set_rules);
    int n = (int) rules.size();
    for (int i = 0; i < rules.size(); i++)
    {
        int left = rules[i].first;
        vector <int> right = rules[i].second;
        if (right.size() <= 2)
        {
            rules_without_long.push_back(rules[i]);
            continue;
        }
        int current_left = left;
        for (int j = 0; j < right.size(); j++)
        {
            if (right.size() - j == 2)
            {
                vector <int> current_right;
                current_right.push_back(right[j]);
                current_right.push_back(right[j + 1]);
                rules_without_long.push_back(make_pair(current_left, current_right));
                break;
            }
            vector <int> current_right;
            current_right.push_back(right[j]);
            current_right.push_back(current_unterminal);
            rules_without_long.push_back(make_pair(current_left, current_right));
            current_left = current_unterminal;
            current_unterminal++;
        }
    }
    set <pair <int, vector <int> > > ans = vec_to_set(rules_without_long);
    return ans;
}

set <int> get_eps_productions()
{
    vector <bool> is_eps((unsigned long) (current_unterminal + 5));
    vector <bool> already_eps((unsigned long) (current_unterminal + 5));
    vector <int> eps_unterms;
    vector <pair <int, vector <int> > > rules = set_to_vec(set_rules);
    int n = (int) rules.size();
    for (int i = 0; i < current_unterminal + 5; i++)
    {
        is_eps[i] = false;
        already_eps[i] = false;
    }
    bool added = true;
    while (added)
    {
        bool added_now = false;
        for (int i = 0; i < n; i++)
        {
            if (already_eps[i])
            {
                continue;
            }
            pair <int, vector <int> > rule = rules[i];
            vector <int> right = rule.second;
            bool new_eps = true;
            for (int j = 0; j < right.size(); j++)
            {
                if (!is_eps[right[j]])
                {
                    new_eps = false;
                    break;
                }
            }
            if (new_eps)
            {
                eps_unterms.push_back(rule.first);
                is_eps[rule.first] = true;
                already_eps[i] = true;
                added_now = true;
            }
        }
        added = added_now;
    }
    set <int> eps_return;
    for (int i = 0; i < eps_unterms.size(); i++)
    {
        eps_return.insert(eps_unterms[i]);
    }
    return eps_return;
}

set <pair <int, vector <int> > > remove_eps_productions()
{
    // start -> eps rule not need because |w| >= 1
    set <int> eps_productions = get_eps_productions();
    vector <pair <int, vector <int> > > rules_without_eps_productions;
    vector <pair <int, vector <int> > > rules = set_to_vec(set_rules);
    int n = (int) rules.size();
    for (int i = 0; i < rules.size(); i++)
    {
        int left = rules[i].first;
        vector <int> right = rules[i].second;
        if (right.size() == 0)
        {
            continue;
        }
        else if (right.size() == 1)
        {
            rules_without_eps_productions.push_back(rules[i]);
            continue;
        }
        else
        {
            if (eps_productions.find(right[0]) == eps_productions.end())
            {
                if (eps_productions.find(right[1]) == eps_productions.end())
                {
                    rules_without_eps_productions.push_back(rules[i]);
                    continue;
                }
                else
                {
                    vector <int> right1;
                    right1.push_back(right[0]);
                    rules_without_eps_productions.push_back(make_pair(left, right1));
                    rules_without_eps_productions.push_back(rules[i]);
                    continue;
                }
            }
            else
            {
                if (eps_productions.find(right[1]) == eps_productions.end())
                {
                    vector <int> right1;
                    right1.push_back(right[1]);
                    rules_without_eps_productions.push_back(make_pair(left, right1));
                    rules_without_eps_productions.push_back(rules[i]);
                    continue;
                }
                else
                {
                    if (right[0] == right[1])
                    {
                        vector <int> right1;
                        right1.push_back(right[0]);
                        rules_without_eps_productions.push_back(make_pair(left, right1));
                        rules_without_eps_productions.push_back(rules[i]);
                        continue;
                    }
                    vector <int> right1, right2;
                    right1.push_back(right[0]);
                    right2.push_back(right[1]);
                    rules_without_eps_productions.push_back(make_pair(left, right1));
                    rules_without_eps_productions.push_back(make_pair(left, right2));
                    rules_without_eps_productions.push_back(rules[i]);
                    continue;
                }
            }
        }
    }
    set <pair <int, vector <int> > > ans = vec_to_set(rules_without_eps_productions);
    return ans;
}

set <pair <int, vector <int> > > remove_unit_rules()
{
    vector <pair <int, vector <int> > > rules_without_unit;
    set <pair <int, int> > unit_rules;
    vector <pair <int, vector <int> > > rules = set_to_vec(set_rules);
    int n = (int) rules.size();
    for (int i = minimal_unterminal; i < current_unterminal; i++)
    {
        unit_rules.insert(make_pair(i, i));
    }
    vector <pair <int, int> > vector_of_unit_rules;
    for (set <pair <int, int> >::iterator it = unit_rules.begin(); it != unit_rules.end(); it++)
    {
        vector_of_unit_rules.push_back(make_pair(it -> first, it -> second));
    }
    for (int i = 0; i < vector_of_unit_rules.size(); i++)
    {
        int unit_left = vector_of_unit_rules[i].first;
        int unit_right = vector_of_unit_rules[i].second;
        for (int j = 0; j < n; j++)
        {
            int left = rules[j].first;
            vector <int> right = rules[j].second;
            if (right.size() != 1)
            {
                continue;
            }
            if (unit_right == left && right[0] >= minimal_unterminal && unit_rules.find(make_pair(unit_left, right[0])) == unit_rules.end())
            {
                unit_rules.insert(make_pair(unit_left, right[0]));
                vector_of_unit_rules.push_back(make_pair(unit_left, right[0]));
            }
        }
    }
    for (int i = 0; i < vector_of_unit_rules.size(); i++)
    {
        int left = vector_of_unit_rules[i].first;
        int right = vector_of_unit_rules[i].second;
        for (int j = 0; j < rules.size(); j++)
        {
            int left1 = rules[j].first;
            vector <int> right1 = rules[j].second;
            if (left1 != right || (right1.size() == 1 && unit_rules.find(make_pair(left1, right1[0])) != unit_rules.end()))
            {
                continue;
            }
            rules_without_unit.push_back(make_pair(left, right1));
        }
    }
    set <pair <int, vector <int> > > ans = vec_to_set(rules_without_unit);
    return ans;
}

set <pair <int, vector <int> > > remove_useless_rules()
{
    vector <pair <int, vector <int> > > rules_without_useless;
    set <int> useless;
    set <int> all_unterminals;
    vector <pair <int, vector <int> > > rules = set_to_vec(set_rules);
    int n = (int) rules.size();
    for (int i = 0; i < rules.size(); i++)
    {
        int left = rules[i].first;
        vector <int> right = rules[i].second;
        all_unterminals.insert(left);
        for (int j = 0; j < right.size(); j++)
        {
            if (right[j] >= minimal_unterminal)
            {
                all_unterminals.insert(right[j]);
            }
        }
    }
    vector <bool> is_generating((unsigned long) (current_unterminal + 5));
    for (int i = 0; i < current_unterminal + 5; i++)
    {
        is_generating[i] = false;
    }
    for (int i = 0; i < n; i++)
    {
        int left = rules[i].first;
        vector <int> right = rules[i].second;
        bool only_terminals = true;
        for (int j = 0; j < right.size(); j++)
        {
            if (right[j] < 'a' || right[j] > 'z')
            {
                only_terminals = false;
            }
        }
        if (only_terminals)
        {
            is_generating[left] = true;
        }
    }
    bool added = true;
    while (added)
    {
        bool added_now = false;
        for (int i = 0; i < n; i++)
        {
            int left = rules[i].first;
            vector <int> right = rules[i].second;
            if (is_generating[left])
            {
                continue;
            }
            bool new_generating = true;
            for (int j = 0; j < right.size(); j++)
            {
                if (right[j] >= minimal_unterminal && !is_generating[right[j]])
                {
                    new_generating = false;
                }
            }
            if (new_generating)
            {
                is_generating[left] = true;
                added_now = true;
            }
        }
        added = added_now;
    }
    for (int i = minimal_unterminal; i <= current_unterminal; i++)
    {
        if (!is_generating[i] && all_unterminals.find(i) != all_unterminals.end())
        {
            useless.insert(i);
        }
    }
    vector <bool> is_reachable((unsigned long) (current_unterminal + 5));
    for (int i = 0; i < current_unterminal + 5; i++)
    {
        is_reachable[i] = false;
    }
    is_reachable[(int) start] = true;
    added = true;
    while (added)
    {
        bool added_now = false;
        for (int i = 0; i < n; i++)
        {
            int left = rules[i].first;
            vector <int> right = rules[i].second;
            if (!is_reachable[left])
            {
                continue;
            }
            bool new_reachable = false;
            for (int j = 0; j < right.size(); j++)
            {
                if (right[j] >= minimal_unterminal)
                {
                    if (!is_reachable[right[j]])
                    {
                        is_reachable[right[j]] = true;
                        new_reachable = true;
                    }
                }
            }
            if (new_reachable)
            {
                added_now = true;
            }
        }
        added = added_now;
    }
    for (int i = minimal_unterminal; i <= current_unterminal; i++)
    {
        if (!is_reachable[i] && all_unterminals.find(i) != all_unterminals.end())
        {
            useless.insert(i);
        }
    }
    for (int i = 0; i < rules.size(); i++)
    {
        int left = rules[i].first;
        vector <int> right = rules[i].second;
        if (useless.find(left) != useless.end())
        {
            continue;
        }
        bool is_useless = false;
        for (int j = 0; j < right.size(); j++)
        {
            if (useless.find(right[j]) != useless.end())
            {
                is_useless = true;
                break;
            }
        }
        if (is_useless)
        {
            continue;
        }
        rules_without_useless.push_back(rules[i]);
    }
    set <pair <int, vector <int> > > ans = vec_to_set(rules_without_useless);
    return ans;
}

set <pair <int, vector <int> > > remove_double_terminals()
{
    vector <pair <int, vector <int> > > rules_without_double_terminals;
    vector <pair <int, vector <int> > > rules = set_to_vec(set_rules);
    int n = (int) rules.size();
    for (int i = 0; i < rules.size(); i++)
    {
        int left = rules[i].first;
        vector <int> right = rules[i].second;
        if (!(right.size() == 2 && ((right[0] >= 'a' && right[0] <= 'z') || (right[1] >= 'a' && right[1] <= 'z'))))
        {
            rules_without_double_terminals.push_back(rules[i]);
            continue;
        }
        if (right[0] >= 'a' && right[0] <= 'z' && (right[1] < 'a' || right[1] > 'z'))
        {
            vector <int> new_right;
            new_right.push_back(letter_to_unterminal[right[0]]);
            new_right.push_back(right[1]);
            rules_without_double_terminals.push_back(make_pair(left, new_right));
            vector <int> right1;
            right1.push_back(right[0]);
            rules_without_double_terminals.push_back(make_pair(letter_to_unterminal[right[0]], right1));
            continue;
        }
        if (right[1] >= 'a' && right[1] <= 'z' && (right[0] < 'a' || right[0] > 'z'))
        {
            vector <int> new_right;
            new_right.push_back(right[0]);
            new_right.push_back(letter_to_unterminal[right[1]]);
            rules_without_double_terminals.push_back(make_pair(left, new_right));
            vector <int> right1;
            right1.push_back(right[1]);
            rules_without_double_terminals.push_back(make_pair(letter_to_unterminal[right[1]], right1));
            continue;
        }
        vector <int> new_right;
        new_right.push_back(letter_to_unterminal[right[0]]);
        new_right.push_back(letter_to_unterminal[right[1]]);
        rules_without_double_terminals.push_back(make_pair(left, new_right));
        vector <int> right1, right2;
        right1.push_back(right[0]);
        right2.push_back(right[1]);
        rules_without_double_terminals.push_back(make_pair(letter_to_unterminal[right[0]], right1));
        rules_without_double_terminals.push_back(make_pair(letter_to_unterminal[right[1]], right2));
    }
    set <pair <int, vector <int> > > ans = vec_to_set(rules_without_double_terminals);
    return ans;
}

bool solve(string word)
{
    vector <pair <int, vector <int> > > rules = set_to_vec(set_rules);
    int n = (int) rules.size();
    vector <vector <vector <bool> > > dp((unsigned long) (current_unterminal - minimal_unterminal + 3));
    for (int i = 0; i < current_unterminal - minimal_unterminal + 3; i++)
    {
        dp[i].resize(101);
        for (int j = 0; j < 101; j++)
        {
            dp[i][j].resize(101);
        }
    }
    int word_size = (int) word.size();
    for (int i = 0; i < current_unterminal - minimal_unterminal; i++)
    {
        for (int j = 0; j < word_size; j++)
        {
            for (int k = 0; k < word_size; k++)
            {
                dp[i][j][k] = false;
            }
        }
    }
    for (int i = 0; i < current_unterminal - minimal_unterminal; i++)
    {
        for (int j = 0; j < word_size; j++)
        {
            for (int k = 0; k < n; k++)
            {
                pair <int, vector <int> > rule = rules[k];
                int left = rule.first;
                vector <int> right = rule.second;
                if (left == i + minimal_unterminal && right[0] == word[j])
                {
                    dp[i][j][j] = true;
                }
            }
        }
    }
    vector <vector <vector <int> > > unterminals_to_rules((unsigned long) (current_unterminal - minimal_unterminal + 3));
    for (int i = 0; i < n; i++)
    {
        int left = rules[i].first;
        vector <int> right = rules[i].second;
        unterminals_to_rules[left - minimal_unterminal].push_back(right);
    }
    for (int j = word_size - 1; j >= 0; j--)
    {
        for (int k = j + 1; k < word_size; k++)
        {
            for (int i = 0; i < current_unterminal - minimal_unterminal; i++)
            {
                for (int l = 0; l < unterminals_to_rules[i].size(); l++)
                {

                    vector <int> right = unterminals_to_rules[i][l];
                    if (right.size() == 2)
                    {
                        for (int p = j; p < k; p++)
                        {
                            dp[i][j][k] = dp[i][j][k] || (dp[right[0] - minimal_unterminal][j][p] && dp[right[1] - minimal_unterminal][p + 1][k]);
                        }
                    }
                }
            }
        }
    }
    return dp[start - minimal_unterminal][0][word_size - 1];
}

void print_debug()
{
    vector <pair <int, vector <int> > > rules = set_to_vec(set_rules);
    int n = (int) rules.size();
    for (int i = 0; i < rules.size(); i++)
    {
        int left = rules[i].first;
        vector <int> right = rules[i].second;
        cerr << left - minimal_unterminal << " -> ";
        for (int j = 0; j < right.size(); j++)
        {
            cerr << right[j] - minimal_unterminal << " ";
        }
        cerr << endl;
    }
    cerr << "--------------------------" << endl;
}

int main()
{
    freopen ("cf.in", "r", stdin);
    freopen ("cf.out", "w", stdout);
    map <int, int> renumber_of_unterminals; // Must renumber because 'a' > 'Z', so I can't guarantee continious numbers of unterminals
    char st;
    cin >> m >> st;
    cin.ignore();
    for (int i = 0; i < m; i++)
    {
        string s1, s3;
        vector <int> right;
        int left;
        string s;
        getline(cin, s);
        s1 = s.substr(0, s.find("->") - 1);
        if (s.find("->") + 3 >= s.size())
        {
            s3 = "";
        }
        else
        {
            s3 = s.substr(s.find("->") + 3);
            bool only_spaces = true;
            for (int j = 0; j < s3.size(); j++)
            {
                if (s3[j] != ' ')
                {
                    only_spaces = false;
                }
            }
            if (only_spaces)
            {
                s3 = "";
            }
        }
        left = s1[0];
        for (int j = 0; j < s3.size(); j++)
        {
            right.push_back(s3[j]);
        }
        if (renumber_of_unterminals.find(left) == renumber_of_unterminals.end())
        {
            renumber_of_unterminals[left] = current_unterminal;
            current_unterminal++;
        }
        for (int j = 0; j < right.size(); j++)
        {
            if (right[j] >= 'A' && right[j] <= 'Z')
            {
                if (renumber_of_unterminals.find(right[j]) == renumber_of_unterminals.end())
                {
                    renumber_of_unterminals[right[j]] = current_unterminal;
                    current_unterminal++;
                }
                right[j] = renumber_of_unterminals[right[j]];
            }
        }
        set_rules.insert(make_pair(renumber_of_unterminals[left], right));
    }
    start = renumber_of_unterminals[(int) st];
    for (int i = 'a'; i <= 'z'; i++)
    {
        letter_to_unterminal[i] = current_unterminal;
        current_unterminal++;
    }
    string word;
    cin >> word;
    set_rules = remove_long_rules();
    //print_debug();
    set_rules = remove_eps_productions();
    //print_debug();
    set_rules = remove_unit_rules();
    //print_debug();
    set_rules = remove_useless_rules();
    //print_debug();
    set_rules = remove_double_terminals();
    //print_debug();
    bool answer = solve(word);
    //print_debug();
    if (answer)
    {
        cout << "yes" << endl;
    }
    else
    {
        cout << "no" << endl;
    }
    return 0;
}