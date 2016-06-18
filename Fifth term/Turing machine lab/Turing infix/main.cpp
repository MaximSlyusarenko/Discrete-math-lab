#include <iostream>

using namespace std;

int main()
{
    freopen ("infixlogic.out", "w", stdout);

    cout << 3 << endl; // first tape - input, second tape - operation stack, third tape - stack of bits

    cout << "S ( _ _ -> S _ > ( > _ ^" << endl;
    cout << "S ) _ _ -> ep 2 ^ _ < _ <" << endl; // ep - evaluate in parenthesis, 2 - to begin from s again (to not duplicate rules)

    cout << "ep 2 a 0 -> and0p 2 ^ _ ^ _ <" << endl; // and0p - and, first arg is 0, in parenthesis
    cout << "ep 2 a 1 -> and1p 2 ^ _ ^ _ <" << endl; // and1p - and, first arg is 1, in parenthesis
    cout << "ep 2 o 0 -> or0p 2 ^ _ ^ _ <" << endl; // or0p - or, first arg is 0, in parenthesis
    cout << "ep 2 o 1 -> or1p 2 ^ _ ^ _ <" << endl; // or1p - or, first arg is 1, in parenthesis

    cout << "and0p 2 _ 0 -> ep 2 ^ _ < 0 ^" << endl;
    cout << "and0p 2 _ 1 -> ep 2 ^ _ < 0 ^" << endl;
    cout << "and1p 2 _ 0 -> ep 2 ^ _ < 0 ^" << endl;
    cout << "and1p 2 _ 1 -> ep 2 ^ _ < 1 ^" << endl;

    cout << "or0p 2 _ 0 -> ep 2 ^ _ < 0 ^" << endl;
    cout << "or0p 2 _ 1 -> ep 2 ^ _ < 1 ^" << endl;
    cout << "or1p 2 _ 0 -> ep 2 ^ _ < 1 ^" << endl;
    cout << "or1p 2 _ 1 -> ep 2 ^ _ < 1 ^" << endl;

    cout << "ep 2 ( 0 -> S _ > _ ^ 0 >" << endl; // evaluated
    cout << "ep 2 ( 1 -> S _ > _ ^ 1 >" << endl; // evaluated
    cout << "ep 2 ( _ -> S _ > _ ^ _ ^" << endl; // evaluated, case - ( )

    cout << "S o _ _ -> epo 2 ^ _ < _ <" << endl; // epo - evaluate, priority or

    cout << "epo 2 a 0 -> and0po 2 ^ _ ^ _ <" << endl; // and0po - and, first arg is 0, priority or
    cout << "epo 2 a 1 -> and1po 2 ^ _ ^ _ <" << endl; // and1po - and, first arg is 1, priority or
    cout << "epo 2 o 0 -> or0po 2 ^ _ ^ _ <" << endl; // or0po - or, first arg is 0, priority or
    cout << "epo 2 o 1 -> or1po 2 ^ _ ^ _ <" << endl; // or1po - or, first arg is 1, priority or

    cout << "and0po 2 _ 0 -> epo 2 ^ _ < 0 ^" << endl;
    cout << "and0po 2 _ 1 -> epo 2 ^ _ < 0 ^" << endl;
    cout << "and1po 2 _ 0 -> epo 2 ^ _ < 0 ^" << endl;
    cout << "and1po 2 _ 1 -> epo 2 ^ _ < 1 ^" << endl;

    cout << "or0po 2 _ 0 -> epo 2 ^ _ < 0 ^" << endl;
    cout << "or0po 2 _ 1 -> epo 2 ^ _ < 1 ^" << endl;
    cout << "or1po 2 _ 0 -> epo 2 ^ _ < 1 ^" << endl;
    cout << "or1po 2 _ 1 -> epo 2 ^ _ < 1 ^" << endl;

    cout << "epo 2 _ 0 -> S _ > o > 0 >" << endl; // evaluated
    cout << "epo 2 _ 1 -> S _ > o > 1 >" << endl; // evaluated

    cout << "epo 2 ( 0 -> wo 2 ^ ( > 0 >" << endl; // wo - write or
    cout << "epo 2 ( 1 -> wo 2 ^ ( > 1 >" << endl;

    cout << "wo 2 _ _ -> S _ > o > _ ^" << endl;

    cout << "S a _ _ -> epa 2 ^ _ < _ <" << endl; // epa - evaluate, priority and

    cout << "epa 2 a 0 -> and0pa 2 ^ _ ^ _ <" << endl; // and0pa - and, first arg is 0, priority and
    cout << "epa 2 a 1 -> and1pa 2 ^ _ ^ _ <" << endl; // and1pa - and, first arg is 1, priority and
    cout << "epa 2 o 0 -> wa 2 ^ o > 0 >" << endl; // wa - write and
    cout << "epa 2 o 1 -> wa 2 ^ o > 1 >" << endl;
    cout << "epa 2 ( 0 -> wa 2 ^ ( > 0 >" << endl;
    cout << "epa 2 ( 1 -> wa 2 ^ ( > 1 >" << endl;

    cout << "and0pa 2 _ 0 -> epa 2 ^ _ < 0 ^" << endl;
    cout << "and0pa 2 _ 1 -> epa 2 ^ _ < 0 ^" << endl;
    cout << "and1pa 2 _ 0 -> epa 2 ^ _ < 0 ^" << endl;
    cout << "and1pa 2 _ 1 -> epa 2 ^ _ < 1 ^" << endl;

    cout << "wa 2 _ _ -> S _ > a > _ ^" << endl;

    cout << "epa 2 _ 0 -> S _ > a > 0 >" << endl;
    cout << "epa 2 _ 1 -> S _ > a > 1 >" << endl;

    cout << "S 0 _ _ -> S _ > _ ^ 0 >" << endl;
    cout << "S 1 _ _ -> S _ > _ ^ 1 >" << endl;

    cout << "S _ _ _ -> ga 2 ^ _ < _ <" << endl; // ga - get answer (input is finished)

    cout << "ga 2 a 0 -> and0ga 2 ^ _ ^ _ <" << endl; // and0ga - and, first arg is 0, get answer
    cout << "ga 2 a 1 -> and1ga 2 ^ _ ^ _ <" << endl; // and1ga - and, first arg is 1, get answer
    cout << "ga 2 o 0 -> or0ga 2 ^ _ ^ _ <" << endl; // or0ga - or, first arg is 0, get answer
    cout << "ga 2 o 1 -> or1ga 2 ^ _ ^ _ <" << endl; // or1ga - or, first arg is 1, get answer

    cout << "and0ga 2 _ 0 -> ga 2 ^ _ < 0 ^" << endl;
    cout << "and0ga 2 _ 1 -> ga 2 ^ _ < 0 ^" << endl;
    cout << "and1ga 2 _ 0 -> ga 2 ^ _ < 0 ^" << endl;
    cout << "and1ga 2 _ 1 -> ga 2 ^ _ < 1 ^" << endl;

    cout << "or0ga 2 _ 0 -> ga 2 ^ _ < 0 ^" << endl;
    cout << "or0ga 2 _ 1 -> ga 2 ^ _ < 1 ^" << endl;
    cout << "or1ga 2 _ 0 -> ga 2 ^ _ < 1 ^" << endl;
    cout << "or1ga 2 _ 1 -> ga 2 ^ _ < 1 ^" << endl;

    cout << "ga 2 _ 0 -> AC 0 ^ _ ^ _ ^" << endl; // evaluated
    cout << "ga 2 _ 1 -> AC 1 ^ _ ^ _ ^" << endl; // evaluated
    return 0;
}