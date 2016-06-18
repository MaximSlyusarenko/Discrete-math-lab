#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    freopen ("convertto2.out", "w", stdout);

    cout << "start: s2" << endl;
    cout << "accept: ac" << endl;
    cout << "reject: rj" << endl;
    cout << "blank: _" << endl;

    cout << "s2 0 -> s2 _ >" << endl;
    cout << "s2 _ -> ac 0 ^" << endl;
    cout << "s2 1 -> s1 1 ^" << endl;
    cout << "s2 2 -> s1 2 ^" << endl;

    cout << "s1 1 -> t4 1 <" << endl;
    cout << "s1 2 -> t4 2 <" << endl;
    cout << "t4 _ -> s 4 >" << endl;

    cout << "s 1 -> o 1 >" << endl; // o = odd number
    cout << "s 2 -> e 2 >" << endl; // e = even number
    cout << "e 0 -> e 0 >" << endl;
    cout << "e 1 -> o 1 >" << endl;
    cout << "e 2 -> e 2 >" << endl;
    cout << "o 0 -> o 0 >" << endl;
    cout << "o 1 -> e 1 >" << endl;
    cout << "o 2 -> o 2 >" << endl;

    cout << "o _ -> w1 _ <" << endl; // w1 = write 1
    cout << "e _ -> w0 _ <" << endl; // w0 = write 0

    cout << "w0 0 -> w0 0 <" << endl;
    cout << "w0 1 -> w0 1 <" << endl;
    cout << "w0 2 -> w0 2 <" << endl;
    cout << "w0 _ -> w0 _ <" << endl;
    cout << "w1 0 -> w1 0 <" << endl;
    cout << "w1 1 -> w1 1 <" << endl;
    cout << "w1 2 -> w1 2 <" << endl;
    cout << "w1 _ -> w1 _ <" << endl;

    cout << "w0 4 -> glw0 4 <" << endl; // glw0 = go left and write 0
    cout << "w1 4 -> glw1 4 <" << endl; // glw1 = go left and write 1

    cout << "glw0 0 -> glw0 0 <" << endl; // go on our binary number
    cout << "glw0 1 -> glw0 1 <" << endl;
    cout << "glw1 0 -> glw1 0 <" << endl;
    cout << "glw1 1 -> glw1 1 <" << endl;
    cout << "glw0 _ -> gtst 0 >" << endl; // gtst = go to start ternary
    cout << "glw1 _ -> gtst 1 >" << endl;

    cout << "gtst 0 -> gtst 0 >" << endl;
    cout << "gtst 1 -> gtst 1 >" << endl;
    cout << "gtst 4 -> sb 4 >" << endl; // sb = skip blanks

    cout << "sb _ -> sb _ >" << endl;
    cout << "sb 0 -> dtr0 0 ^" << endl; // dtr0 = divide ternary on 2, remainder = 0, struct of tape = binary + 4 + current ternary
    cout << "sb 1 -> dtr0 1 ^" << endl;
    cout << "sb 2 -> dtr0 2 ^" << endl;

    cout << "dtr0 0 -> w0r0 _ >" << endl; // w0r0 = write 0, remainder 0
    cout << "dtr0 1 -> w0r1 _ >" << endl; // w0r1 = write 0, remainder 1
    cout << "dtr0 2 -> w1r0 _ >" << endl; // w1r0 = write 1, remainder 0
    cout << "dtr0 _ -> s _ >" << endl;

    cout << "dtr1 0 -> w1r1 _ >" << endl; // w1r1 = write 1, remainder 1
    cout << "dtr1 1 -> w2r0 _ >" << endl; // w2r0 = write 2, remainder 0
    cout << "dtr1 2 -> w2r1 _ >" << endl; // w2r1 = write 2, remainder 1
    cout << "dtr1 _ -> s _ >" << endl;

    cout << "w0r0 0 -> w0r0 0 >" << endl;
    cout << "w0r0 1 -> w0r0 1 >" << endl;
    cout << "w0r0 2 -> w0r0 2 >" << endl;
    cout << "w0r1 0 -> w0r1 0 >" << endl;
    cout << "w0r1 1 -> w0r1 1 >" << endl;
    cout << "w0r1 2 -> w0r1 2 >" << endl;
    cout << "w1r0 0 -> w1r0 0 >" << endl;
    cout << "w1r0 1 -> w1r0 1 >" << endl;
    cout << "w1r0 2 -> w1r0 2 >" << endl;
    cout << "w1r1 0 -> w1r1 0 >" << endl;
    cout << "w1r1 1 -> w1r1 1 >" << endl;
    cout << "w1r1 2 -> w1r1 2 >" << endl;
    cout << "w2r0 0 -> w2r0 0 >" << endl;
    cout << "w2r0 1 -> w2r0 1 >" << endl;
    cout << "w2r0 2 -> w2r0 2 >" << endl;
    cout << "w2r1 0 -> w2r1 0 >" << endl;
    cout << "w2r1 1 -> w2r1 1 >" << endl;
    cout << "w2r1 2 -> w2r1 2 >" << endl;

    cout << "w0r0 _ -> w0r0h _ >" << endl; // w0r0h = write 0, remainder 0, here
    cout << "w0r1 _ -> w0r1h _ >" << endl; // w0r1h = write 0, remainder 1, here
    cout << "w1r0 _ -> w1r0h _ >" << endl; // w1r0h = write 1, remainder 0, here
    cout << "w1r1 _ -> w1r1h _ >" << endl; // w1r1h = write 1, remainder 1, here
    cout << "w2r0 _ -> w2r0h _ >" << endl; // w2r0h = write 2, remainder 0, here
    cout << "w2r1 _ -> w2r1h _ >" << endl; // w2r1h = write 2, remainder 1, here

    cout << "w0r0h 0 -> w0r0h 0 >" << endl;
    cout << "w0r0h 1 -> w0r0h 1 >" << endl;
    cout << "w0r0h 2 -> w0r0h 2 >" << endl;
    cout << "w0r1h 0 -> w0r1h 0 >" << endl;
    cout << "w0r1h 1 -> w0r1h 1 >" << endl;
    cout << "w0r1h 2 -> w0r1h 2 >" << endl;
    cout << "w1r0h 0 -> w1r0h 0 >" << endl;
    cout << "w1r0h 1 -> w1r0h 1 >" << endl;
    cout << "w1r0h 2 -> w1r0h 2 >" << endl;
    cout << "w1r1h 0 -> w1r1h 0 >" << endl;
    cout << "w1r1h 1 -> w1r1h 1 >" << endl;
    cout << "w1r1h 2 -> w1r1h 2 >" << endl;
    cout << "w2r0h 0 -> w2r0h 0 >" << endl;
    cout << "w2r0h 1 -> w2r0h 1 >" << endl;
    cout << "w2r0h 2 -> w2r0h 2 >" << endl;
    cout << "w2r1h 0 -> w2r1h 0 >" << endl;
    cout << "w2r1h 1 -> w2r1h 1 >" << endl;
    cout << "w2r1h 2 -> w2r1h 2 >" << endl;

    cout << "w0r0h _ -> r0rts 0 <" << endl; // r0rts = remainder 0, return to start
    cout << "w0r1h _ -> r1rts 0 <" << endl; // r1rts = remainder 1, return to start
    cout << "w1r0h _ -> r0rts 1 <" << endl;
    cout << "w1r1h _ -> r1rts 1 <" << endl;
    cout << "w2r0h _ -> r0rts 2 <" << endl;
    cout << "w2r1h _ -> r1rts 2 <" << endl;

    cout << "r0rts 0 -> r0rts 0 <" << endl;
    cout << "r0rts 1 -> r0rts 1 <" << endl;
    cout << "r0rts 2 -> r0rts 2 <" << endl;
    cout << "r1rts 0 -> r1rts 0 <" << endl;
    cout << "r1rts 1 -> r1rts 1 <" << endl;
    cout << "r1rts 2 -> r1rts 2 <" << endl;

    cout << "r0rts _ -> r0rtsf _ <" << endl; // r0rtsf = remainder 0, return to start finally (stop on blank)
    cout << "r1rts _ -> r1rtsf _ <" << endl;

    cout << "r0rtsf 0 -> r0rtsf 0 <" << endl;
    cout << "r0rtsf 1 -> r0rtsf 1 <" << endl;
    cout << "r0rtsf 2 -> r0rtsf 2 <" << endl;
    cout << "r1rtsf 0 -> r1rtsf 0 <" << endl;
    cout << "r1rtsf 1 -> r1rtsf 1 <" << endl;
    cout << "r1rtsf 2 -> r1rtsf 2 <" << endl;

    cout << "r0rtsf _ -> dtr0 _ >" << endl;
    cout << "r1rtsf _ -> dtr1 _ >" << endl;
    cout << "r0rtsf 4 -> rtcw 4 >" << endl; // rtcw = return to current word, last word is finished
    cout << "r1rtsf 4 -> rtcw 4 >" << endl;

    cout << "rtcw _ -> rtcw _ >" << endl;
    cout << "rtcw 0 -> s 0 ^" << endl;
    cout << "rtcw 1 -> s 1 ^" << endl;
    cout << "rtcw 2 -> s 2 ^" << endl;

    cout << "s 0 -> mf _ >" << endl; // mf = maybe finished
    cout << "mf 1 -> s 1 ^" << endl;
    cout << "mf 2 -> s 2 ^" << endl;
    cout << "mf 0 -> mf _ >" << endl;
    cout << "mf _ -> f _ <" << endl; // f = finished

    cout << "f _ -> f _ <" << endl;
    cout << "f 4 -> tsbw _ <" << endl; // tsbw = to start binary word
    cout << "tsbw 0 -> tsbw 0 <" << endl;
    cout << "tsbw 1 -> tsbw 1 <" << endl;
    cout << "tsbw _ -> ac _ >" << endl;

    return 0;
}