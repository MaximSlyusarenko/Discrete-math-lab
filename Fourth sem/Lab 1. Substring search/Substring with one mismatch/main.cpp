#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

/**
* Построим z-функцию для строки, как в алгоритме КМП и для такой же строки, только с развернутыми образцом и текстом.
* По значениям 2 этих z-функций мы можем определить, сколько символог, начиная с i-го символа текста совпадает
* с суффиксом образца и также сколько символов совпадает с префиксом. По этим данным мы можем проверить, больше 1 несовпадения
* в тексте, начиная с i-ой позиции и в образце, или меньше или равно одного совпадения. В зависимости от этого, будем находить ответ
*/

string p, t;
int z[2000002], z1[2000002];
vector <int> ans;

void z_function(string pattern, int n, int* z)
{
    int left = 0;
    int right = 0;
    for (int i = 1; i < n; i++)
    {
        z[i] = max(0, min(right - i, z[i - left]));
        while (i + z[i] < n && pattern[z[i]] == pattern[i + z[i]])
        {
            z[i]++;
        }
        if (i + z[i] >= right)
        {
            left = i;
            right = i + z[i];
        }
    }
}

void reverse_string(string &s)
{
    for (int i = 0; i < s.size() / 2; i++)
    {
        char tmp = s[i];
        s[i] = s[s.size() - i - 1];
        s[s.size() - i - 1] = tmp;
    }
}

int main()
{
    ifstream in("search3.in");
    ofstream out("search3.out");
    in >> p >> t;
    if (p.size() > t.size())
    {
        out << 0;
        return 0;
    }
    string for_z = p;
    for_z += "#";
    for_z += t;
    z_function(for_z, (int) for_z.size(), z);
    reverse_string(p);
    reverse_string(t);
    string for_z1 = p;
    for_z1 += "#";
    for_z1 += t;
    z_function(for_z1, (int) for_z1.size(), z1);
    for (int i = 0; i < t.size() - p.size() + 1; i++)
    {
        int add = (int) p.size() + 1;
        int curz = z[add + i];
        int curz1 = z1[add + t.size() - i - p.size()];
        if (curz + curz1 >= p.size() - 1)
        {
            ans.push_back(i + 1);
        }
    }
    out << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        out << ans[i] << " ";
    }
    return 0;
}