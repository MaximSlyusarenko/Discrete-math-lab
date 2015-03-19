#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>

using namespace std;

string t, p;
vector <int> positions;

int main()
{
    ifstream in("search1.in");
    ofstream out("search1.out");
    in >> p >> t;
    if (t.size() < p.size())
    {
        out << 0;
        return 0;
    }
    for (int i = 0; i <= t.size() - p.size(); i++)
    {
        bool substring = true;
        for (int j = 0; j < p.size(); j++)
        {
            if (t[i + j] != p[j])
            {
                substring = false;
            }
        }
        if (substring)
        {
            positions.push_back(i + 1);
        }
    }
    out << positions.size() << endl;
    for (int i = 0; i < positions.size(); i++)
    {
        out << positions[i] << " ";
    }
    return 0;
}