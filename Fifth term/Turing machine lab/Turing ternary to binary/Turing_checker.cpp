#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <string>

using namespace std;

const string START = "start: ";
const string ACCEPT = "accept: ";
const string REJECT = "reject: ";
const string BLANK = "blank: ";
string for_tape = "_______________________________________________________________________________________________________________________________________________________________";
int our_pos;
string cur_state;
map <pair <string, string>, pair <pair <string, string>, string> > transitions;
string start, accept, reject, blank;

string to_ternary(int num)
{
    string ans = "";
    while (num > 0)
    {
        ans += (num % 3) + '0';
        num /= 3;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

bool check(int l)
{
    string ternary_input = to_ternary(l);
    string tape = for_tape + ternary_input + for_tape;
    int i = 0;
    while (i < tape.size())
    {
        if (tape[i] == '_')
        {
            i++;
            continue;
        }
        break;
    }
    our_pos = i;
    cur_state = start;
    string ternary;
    for (int j = our_pos; tape[j] != '_'; j++)
    {
        ternary += tape[j];
    }

    while (cur_state != accept && cur_state != reject)
    {
        string cur_symb = "a";
        cur_symb[0] = tape[our_pos];
        //cerr << cur_state << " " << cur_symb << endl;
        if (transitions.find(make_pair(cur_state, cur_symb)) == transitions.end())
        {
            cur_state = reject;
        }
        else
        {
            pair <pair <string, string>, string> cur_transition = transitions[make_pair(cur_state, cur_symb)];
            cur_state = cur_transition.first.first;
            tape[our_pos] = cur_transition.first.second[0];
            string move = cur_transition.second;
            if (move[0] == '>')
            {
                our_pos++;
            }
            else if (move[0] == '<')
            {
                our_pos--;
            }
        }
        /*cerr << tape << endl;
        for (int j = 0; j < our_pos; j++)
        {
            cerr << "_";
        }
        cerr << "^" << endl;*/

    }
    //cerr << "FINISH: cur_state = " << cur_state << endl;
    //cerr << tape << endl;
    string result;
    int r;
    for (r = our_pos; tape[r] != '_'; r++)
    {
        result += tape[r];
    }

    bool nothing_other_on_machine = true;
    for (int j = 0; j < our_pos; j++)
    {
        if (tape[j] != '_')
        {
            nothing_other_on_machine = false;
        }
    }

    for (int j = r; j < tape.size(); j++)
    {
        if (tape[j] != '_')
        {
            nothing_other_on_machine = false;
        }
    }

    int ternary_to_decimal = 0;
    int p = 1;
    for (int j = (int) (ternary.size() - 1); j >= 0; j--)
    {
        int q = ternary[j] - '0';
        ternary_to_decimal += q * p;
        p *= 3;
    }

    int binary_to_decimal = 0;
    p = 1;
    for (int j = (int) (result.size() - 1); j >= 0; j--)
    {
        int q = result[j] - '0';
        binary_to_decimal += p * q;
        p *= 2;
    }

    if (ternary_to_decimal == binary_to_decimal && cur_state == "ac" && result[0] != '0' && nothing_other_on_machine)
    {
        //cerr << "OK" << endl;
        return true;
    }
    else
    {
        //cerr << "FAIL" << endl;
        return false;
    }
}

int main()
{
    freopen ("convertto2.out", "r", stdin);

    getline(cin, start);
    getline(cin, accept);
    getline(cin, reject);
    getline(cin, blank);
    start = start.substr(START.size());
    accept = accept.substr(ACCEPT.size());
    reject = reject.substr(REJECT.size());
    blank = blank.substr(BLANK.size());

    string tmp;
    while (getline(cin, tmp))
    {
        string from = tmp.substr(0, tmp.find(" "));
        tmp = tmp.substr(tmp.find(" ") + 1);
        string symbol = tmp.substr(0, tmp.find(" "));
        tmp = tmp.substr(tmp.find(" ") + 4);
        string to = tmp.substr(0, tmp.find(" "));
        tmp = tmp.substr(tmp.find(" ") + 1);
        string write = tmp.substr(0, tmp.find(" "));
        tmp = tmp.substr(tmp.find(" ") + 1);
        string must_do = tmp;
        //cerr << from << "|" << symbol << "|" << to << "|" << write << "|" << must_do << "|" << endl;
        transitions.insert(make_pair(make_pair(from, symbol), make_pair(make_pair(to, write), must_do)));
    }

    for (int i = 1; i < 120000; i++)
    {
        cerr << i << endl;
        if (!check(i))
        {
            cerr << "FAIL on i = " << i << endl;
            return 0;
        }
    }

    return 0;
}
