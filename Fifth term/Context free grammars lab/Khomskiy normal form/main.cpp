#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

char s;
int n, word_size;
vector <pair <string, string> > rules;
long long dp[100][200][200];
string word;

int main()
{
    freopen ("nfc.in", "r", stdin);
    freopen ("nfc.out", "w", stdout);
    cin >> n >> s;
    for (int i = 0; i < n; i++)
    {
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;
        rules.push_back(make_pair(s1, s3));
    }
    cin >> word;
    word_size = (int) word.size();
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < word_size; j++)
        {
            for (int k = 0; k < word_size; k++)
            {
                dp[i][j][k] = 0;
            }
        }
    }
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < word_size; j++)
        {
            for (int k = 0; k < n; k++)
            {
                pair <string, string> rule = rules[k];
                string left = rule.first;
                string right = rule.second;
                if (left[0] == i + 'A' && right[0] == word[j])
                {
                    dp[i][j][j] = 1;
                }
            }
        }
    }
    for (int j = word_size - 1; j >= 0; j--)
    {
        for (int k = j + 1; k < word_size; k++)
        {
            for (int i = 0; i < 26; i++)
            {
                for (int l = 0; l < n; l++)
                {
                    pair <string, string> rule = rules[l];
                    string left = rule.first;
                    string right = rule.second;
                    if (left[0] == i + 'A' && right.size() == 2)
                    {
                        for (int p = j; p < k; p++)
                        {
                            dp[i][j][k] += (dp[right[0] - 'A'][j][p] * dp[right[1] - 'A'][p + 1][k]) % 1000000007;
                            dp[i][j][k] %= 1000000007;
                        }
                    }
                }
            }
        }
    }
    cout << dp[s - 'A'][0][word_size - 1] << endl;
    return 0;
}