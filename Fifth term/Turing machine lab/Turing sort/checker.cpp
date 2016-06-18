#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <string>

using namespace std;

struct my_left
{
    string state;
    vector <string> tapes;

    bool operator <(const my_left& b) const
    {
        if (this -> state < b.state)
        {
            return true;
        }
        else if (this -> state == b.state)
        {
            for (int i = 0; i < this -> tapes.size(); i++)
            {
                if (this -> tapes[i] < b.tapes[i])
                {
                    return true;
                }
                else if (this -> tapes[i] > b.tapes[i])
                {
                    return false;
                }
            }
        }
        return false;
    }
};

struct my_right
{
    string state;
    vector <pair <string, string> > do_with_tapes;
};

string for_tape = "________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________";
//string for_tape = "_________________________________________________________________________________________________________";
string input_for_machine;
vector <int> our_pos;
vector <string> tapes;
string cur_state;
map <my_left, my_right> transitions;
int number_of_tapes;
string start = "S", accept = "AC", reject = "RJ", blank = "_";

void go_turing()
{
    tapes.push_back(for_tape + input_for_machine + for_tape);
    our_pos.push_back((int &&) for_tape.size());
    for (int i = 0; i < number_of_tapes - 1; i++)
    {
        tapes.push_back(for_tape + for_tape);
        our_pos.push_back((int &&) for_tape.size());
    }
    cur_state = start;
    int it_num = 0;
    while (cur_state != "AC" && cur_state != "RJ")
    {
        /*cerr << it_num << endl << cur_state << endl;
        for (int i = 0; i < number_of_tapes; i++)
        {
            cerr << tapes[i] << endl;
            for (int j = 0; j < our_pos[i]; j++)
            {
                cerr << "-";
            }
            cerr << "^";
            for (int j = 0; j < 10; j++)
            {
                cerr << "-";
            }
            cerr << endl;
        }*/
        my_left left1;
        left1.state = cur_state;
        for (int i = 0; i < number_of_tapes; i++)
        {
            char tmp = tapes[i][our_pos[i]];
            string add = "";
            add += tmp;
            left1.tapes.push_back(add);
        }
        if (transitions.find(left1) == transitions.end())
        {
            my_left check;
            cur_state = "RJ";
        }
        else
        {
            my_right right1 = transitions[left1];
            cur_state = right1.state;
            for (int i = 0; i < number_of_tapes; i++)
            {
                tapes[i][our_pos[i]] = right1.do_with_tapes[i].first[0];
                string going = right1.do_with_tapes[i].second;
                if (going == "<")
                {
                    our_pos[i]--;
                }
                else if (going == ">")
                {
                    our_pos[i]++;
                }
            }
            it_num++;
        }
    }
    /*if (cur_state == "RJ")
    {
        cout << "Very sad..." << endl;
    }
    else
    {
        //cout << tapes[0].substr((unsigned long) our_pos[0]) << endl;
        cout << tapes[0] << endl;
        for (int i = 0; i < our_pos[0]; i++)
        {
            cout << "-";
        }
        cout << "^" << endl;
    }*/
}

pair <my_left, string> parse_left(string tmp)
{
    my_left ans;
    string from = tmp.substr(0, tmp.find(" "));
    ans.state = from;
    tmp = tmp.substr(tmp.find(" ") + 1);
    for (int i = 0; i < number_of_tapes; i++)
    {
        string symbol = tmp.substr(0, tmp.find(" "));
        ans.tapes.push_back(symbol);
        tmp = tmp.substr(tmp.find(" ") + 1);
    }
    return make_pair(ans, tmp);
}

my_right parse_right(string tmp)
{
    my_right ans;
    string to = tmp.substr(0, tmp.find(" "));
    ans.state = to;
    tmp = tmp.substr(tmp.find(" ") + 1);
    for (int i = 0; i < number_of_tapes; i++)
    {
        string symbol = tmp.substr(0, tmp.find(" "));
        tmp = tmp.substr(tmp.find(" ") + 1);
        string doing;
        if (i == number_of_tapes - 1)
        {
            doing = tmp;
        }
        else
        {
            doing = tmp.substr(0, tmp.find(" "));
            tmp = tmp.substr(tmp.find(" ") + 1);
        }
        ans.do_with_tapes.push_back(make_pair(symbol, doing));
    }
    return ans;
}

string to_binary(int q)
{
    if (q == 0)
    {
        return "0";
    }
    string ans = "";
    while (q > 0)
    {
        ans += (char) ('0' + q % 2);
        q /= 2;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int to_decimal(string binary)
{
    int q = 1, res = 0;
    for (int i = (int) (binary.size() - 1); i >= 0; i--)
    {
        res += ((int) (binary[i] - '0')) * q;
        q *= 2;
    }
    return res;
}

bool check_result(vector <string> input, string result)
{
    for (int i = 0; i < our_pos[0]; i++)
    {
        if (result[i] != '_')
        {
            cerr << 1 << endl;
            return false;
        }
    }
    result = result.substr((unsigned long) our_pos[0]);
    int q = 0;
    while (result[q] == '0' || result[q] == '1' || result[q] == '|')
    {
        q++;
    }
    for (int i = q; i < result.size(); i++)
    {
        if (result[i] != '_')
        {
            cerr << 2 << endl;
            return false;
        }
    }
    string ans = result.substr(0, (unsigned long) q);
    string real_ans = "";
    vector <int> decimal_input;
    for (int i = 0; i < input.size(); i++)
    {
        decimal_input.push_back(to_decimal(input[i]));
    }
    sort(decimal_input.begin(), decimal_input.end());
    for (int i = 0; i < decimal_input.size(); i++)
    {
        //cerr << decimal_input[i] << " " << to_binary(decimal_input[i]) << endl;
        real_ans += to_binary(decimal_input[i]) + "|";
    }
    real_ans = real_ans.substr(0, real_ans.size() - 1);
    if (real_ans != ans)
    {
        cerr << ans << endl << real_ans << endl;
        cerr << 3 << endl;
    }
    return (real_ans == ans);
}

int main()
{
    //cin >> input_for_machine;
    freopen ("sorting.out", "r", stdin);

    cin >> number_of_tapes;
    string tmp;
    cin.ignore();
    while (getline(cin, tmp))
    {
        my_left l;
        my_right r;
        pair <my_left, string> q = parse_left(tmp);
        l = q.first;
        tmp = q.second;
        tmp = tmp.substr(3);
        r = parse_right(tmp);
        transitions[l] = r;
    }
    //go_turing();
    for (int i = 0; i < 1000; i++)
    {
        vector <string> input;
        int t = rand() % 20;
        if (t == 0)
        {
            t++;
        }
        for (int j = 0; j < t; j++)
        {
            int q = rand() % 1000;
            string binary = to_binary(q);
            input.push_back(binary);
            input_for_machine += binary + '|';
        }
        input_for_machine = input_for_machine.substr(0, input_for_machine.size() - 1);
        go_turing();
        if (!check_result(input, tapes[0]))
        {
            cout << "bad on test: " << input_for_machine << endl;
            return 0;
        }
        tapes.clear();
        our_pos.clear();
        input.clear();
        input_for_machine = "";
        cerr << i << endl;
    }
    return 0;
}
