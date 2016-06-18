#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    freopen ("reverse.out", "w", stdout);

    // Problem: after last letter of beginning word we will go left infinitely
    // fix: let put 2 on tape to understand where the word is finished (and if we go left and get 2 then we have done everything and must go to the beginning of the word)

    cout << "start: s" << endl;
    cout << "accept: ac" << endl; // rejected not need, as I think
    cout << "reject: rj" << endl; // not need
    cout << "blank: _" << endl;

    cout << "s 0 -> gb 0 >" << endl; // gb = go before blanks
    cout << "s 1 -> gb 1 >" << endl;
    cout << "gb 0 -> gb 0 >" << endl;
    cout << "gb 1 -> gb 1 >" << endl;
    cout << "gb _ -> gts 2 <" << endl; // gts = go to the start

    cout << "gts 1 -> gts 1 <" << endl;
    cout << "gts 0 -> gts 0 <" << endl;
    cout << "gts _ -> s1 _ >" << endl; // s1 = "second start" = start after putting 2 on the tape

    cout << "s1 0 -> gl0 _ <" << endl; // gl0 = go left and write 0
    cout << "s1 1 -> gl1 _ <" << endl; // gl1 = go left and write 1
    cout << "gl0 _ -> gw 0 >" << endl; // gw = go to word
    cout << "gl1 _ -> gw 1 >" << endl;

    cout << "gw _ -> gw _ >" << endl;

    cout << "gw 0 -> gl0osb _ <" << endl; // gl0osb = go left and write 0 on second blanks
    cout << "gw 1 -> gl1osb _ <" << endl; // gl1osb = go left and write 1 on second blanks
    cout << "gl0osb _ -> gl0osb _ <" << endl;
    cout << "gl0osb 0 -> gl0ob 0 <" << endl; // gl0ob = go left and write 0 on blanks (first)
    cout << "gl0osb 1 -> gl0ob 1 <" << endl;
    cout << "gl0ob 0 -> gl0ob 0 <" << endl;
    cout << "gl0ob 1 -> gl0ob 1 <" << endl;
    cout << "gl0ob _ -> gsw 0 >" << endl; // gsw = go to second word (Turing machine now looks like: "part of reversed word + _ + _ + ... + _ + part of input word"
    cout << "gl1osb _ -> gl1osb _ <" << endl;
    cout << "gl1osb 0 -> gl1ob 0 <" << endl; // gl1ob = go left and write 1 on blanks (first)
    cout << "gl1osb 1 -> gl1ob 1 <" << endl;
    cout << "gl1ob 0 -> gl1ob 0 <" << endl;
    cout << "gl1ob 1 -> gl1ob 1 <" << endl;
    cout << "gl1ob _ -> gsw 1 >" << endl; // gsw = go to second word

    cout << "gsw 0 -> gsw 0 >" << endl;
    cout << "gsw 1 -> gsw 1 >" << endl;
    cout << "gsw _ -> gw _ >" << endl;

    cout << "gw 2 -> gsac _ <" << endl; // gsac = go to the start and accept (here is my fix)
    // can't be "gsw 2", because word size is no smaller then 1, so we will see some digits of reversed word and space after these digits

    cout << "gsac _ -> gsac _ <" << endl;
    cout << "gsac 0 -> gbac 0 <" << endl; // gbac = go to the blanks and accept
    cout << "gsac 1 -> gbac 1 <" << endl;

    cout << "gbac 0 -> gbac 0 <" << endl;
    cout << "gbac 1 -> gbac 1 <" << endl;
    cout << "gbac _ -> ac _ >" << endl; // ac = accepted!!!
    return 0;
}