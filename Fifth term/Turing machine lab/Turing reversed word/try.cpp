#include <iostream>

using namespace std;

int main()
{
    freopen ("zero.out", "w", stdout);

    cout << "start: s" << endl;
    cout << "accept: ac" << endl;
    cout << "reject: rj" << endl;
    cout << "blank: _" << endl;
    cout << "s _ -> ac _ ^" << endl;
    cout << "s 0 -> n _ >" << endl;
    cout << "n 0 -> s _ >" << endl;
    cout << "n _ -> rj _ >" << endl;
    return 0;
}

