#include <iostream>

using namespace std;

int main()
{
    freopen ("sorting.out", "w", stdout);

    cout << 3 << endl; // first tape - input, second tape - current max, third tape - minimal element to swap

    cout << "S 0 _ _ -> S 0 > _ ^ _ ^" << endl;
    cout << "S 1 _ _ -> S 1 > _ ^ _ ^" << endl;
    cout << "S | _ _ -> S | > _ ^ _ ^" << endl;
    cout << "S _ _ _ -> rs 2 < _ ^ _ ^" << endl; // rs - return to start

    cout << "rs 0 _ _ -> rs 0 < _ ^ _ ^" << endl;
    cout << "rs 1 _ _ -> rs 1 < _ ^ _ ^" << endl;
    cout << "rs | _ _ -> rs | < _ ^ _ ^" << endl;
    cout << "rs _ _ _ -> s1 _ > _ ^ _ ^" << endl; // s1 - start 1

    cout << "s1 0 _ _ -> s1 0 > 0 > _ ^" << endl;
    cout << "s1 1 _ _ -> s1 1 > 1 > _ ^" << endl;
    cout << "s1 | _ _ -> rtsst | > _ < _ ^" << endl; // rtsst - return to start second tape
    cout << "s1 2 _ _ -> rtsstclstrtsft 2 < _ < _ ^" << endl; // rtsstclstrtsft - written below

    cout << "rtsst 0 0 _ -> rtsst 0 ^ 0 < _ ^" << endl;
    cout << "rtsst 0 1 _ -> rtsst 0 ^ 1 < _ ^" << endl;
    cout << "rtsst 0 _ _ -> comp 0 ^ _ > _ ^" << endl; // comp - compare
    cout << "rtsst 1 0 _ -> rtsst 1 ^ 0 < _ ^" << endl;
    cout << "rtsst 1 1 _ -> rtsst 1 ^ 1 < _ ^" << endl;
    cout << "rtsst 1 _ _ -> comp 1 ^ _ > _ ^" << endl; // comp - compare

    cout << "comp 0 0 _ -> comp 0 > 0 > _ ^" << endl;
    cout << "comp 0 1 _ -> ml 0 > 1 > _ ^" << endl; // ml - maybe less
    cout << "comp 1 0 _ -> mg 1 > 0 > _ ^" << endl; // mg - maybe greater
    cout << "comp 1 1 _ -> comp 1 > 1 > _ ^" << endl;

    cout << "comp | _ _ -> rtsst | > _ < _ ^" << endl; // equals
    cout << "comp 2 _ _ -> rtsstclstrtsft 2 < _ < _ ^" << endl; // equals with last

    cout << "comp | 0 _ -> lrts | < 0 < _ ^" << endl; // lrts - less, return to start, need to swap
    cout << "comp | 1 _ -> lrts | < 1 < _ ^" << endl;

    cout << "comp 2 0 _ -> lrts 2 < 0 < _ ^" << endl; // if it's the last number, so it finishes with 2
    cout << "comp 2 1 _ -> lrts 2 < 1 < _ ^" << endl;

    cout << "comp 0 _ _ -> grts 0 < _ < _ ^" << endl; // grts - greader, return to start, need to change max
    cout << "comp 1 _ _ -> grts 1 < _ < _ ^" << endl;

    cout << "ml 0 0 _ -> ml 0 > 0 > _ ^" << endl;
    cout << "ml 0 1 _ -> ml 0 > 1 > _ ^" << endl;
    cout << "ml 1 0 _ -> ml 1 > 0 > _ ^" << endl;
    cout << "ml 1 1 _ -> ml 1 > 1 > _ ^" << endl;
    cout << "ml | 0 _ -> lrts | < 0 < _ ^" << endl;
    cout << "ml | 1 _ -> lrts | < 1 < _ ^" << endl;
    cout << "ml 2 0 _ -> lrts 2 < 0 < _ ^" << endl;
    cout << "ml 2 1 _ -> lrts 2 < 1 < _ ^" << endl;
    cout << "ml | _ _ -> lrts | < _ < _ ^" << endl;
    cout << "ml 2 _ _ -> lrts 2 < _ < _ ^" << endl;
    cout << "ml 0 _ _ -> grts 0 < _ < _ ^" << endl;
    cout << "ml 1 _ _ -> grts 1 < _ < _ ^" << endl;

    cout << "mg 0 0 _ -> mg 0 > 0 > _ ^" << endl;
    cout << "mg 0 1 _ -> mg 0 > 1 > _ ^" << endl;
    cout << "mg 1 0 _ -> mg 1 > 0 > _ ^" << endl;
    cout << "mg 1 1 _ -> mg 1 > 1 > _ ^" << endl;
    cout << "mg | 0 _ -> lrts | < 0 < _ ^" << endl;
    cout << "mg | 1 _ -> lrts | < 1 < _ ^" << endl;
    cout << "mg 2 0 _ -> lrts 2 < 0 < _ ^" << endl;
    cout << "mg 2 1 _ -> lrts 2 < 1 < _ ^" << endl;
    cout << "mg | _ _ -> grts | < _ < _ ^" << endl;
    cout << "mg 2 _ _ -> grts 2 < _ < _ ^" << endl;
    cout << "mg 0 _ _ -> grts 0 < _ < _ ^" << endl;
    cout << "mg 1 _ _ -> grts 1 < _ < _ ^" << endl;

    cout << "lrts 0 0 _ -> lrts 0 < 0 < 0 <" << endl;
    cout << "lrts 0 1 _ -> lrts 0 < 1 < 0 <" << endl;
    cout << "lrts 1 0 _ -> lrts 1 < 0 < 1 <" << endl;
    cout << "lrts 1 1 _ -> lrts 1 < 1 < 1 <" << endl;
    cout << "lrts | _ _ -> lsw | < _ > _ >" << endl; // lsw - less, skip word

    cout << "lsw 0 0 0 -> lsw 0 < 0 ^ 0 ^" << endl;
    cout << "lsw 0 0 1 -> lsw 0 < 0 ^ 1 ^" << endl;
    cout << "lsw 0 1 0 -> lsw 0 < 1 ^ 0 ^" << endl;
    cout << "lsw 0 1 1 -> lsw 0 < 1 ^ 1 ^" << endl;
    cout << "lsw 1 0 0 -> lsw 1 < 0 ^ 0 ^" << endl;
    cout << "lsw 1 0 1 -> lsw 1 < 0 ^ 1 ^" << endl;
    cout << "lsw 1 1 0 -> lsw 1 < 1 ^ 0 ^" << endl;
    cout << "lsw 1 1 1 -> lsw 1 < 1 ^ 1 ^" << endl;
    cout << "lsw | 0 0 -> ls | > 0 ^ 0 ^" << endl; // ls - less (first tape is less then second), swap
    cout << "lsw | 0 1 -> ls | > 0 ^ 1 ^" << endl;
    cout << "lsw | 1 0 -> ls | > 1 ^ 0 ^" << endl;
    cout << "lsw | 1 1 -> ls | > 1 ^ 1 ^" << endl;
    cout << "lsw _ 0 0 -> ls _ > 0 ^ 0 ^" << endl; // if it's first number
    cout << "lsw _ 0 1 -> ls _ > 0 ^ 1 ^" << endl;
    cout << "lsw _ 1 0 -> ls _ > 1 ^ 0 ^" << endl;
    cout << "lsw _ 1 1 -> ls _ > 1 ^ 1 ^" << endl;

    cout << "grts 0 0 _ -> grts 0 < 0 < _ ^" << endl;
    cout << "grts 0 1 _ -> grts 0 < 1 < _ ^" << endl;
    cout << "grts 1 0 _ -> grts 1 < 0 < _ ^" << endl;
    cout << "grts 1 1 _ -> grts 1 < 1 < _ ^" << endl;
    cout << "grts | _ _ -> gcm | > _ > _ ^" << endl; // gcm - greater (first tape is greater then second), change max
    cout << "grts _ _ _ -> gcm _ > _ > _ ^" << endl; // if it's first number

    cout << "gcm 0 0 _ -> gcm 0 > 0 > _ ^" << endl;
    cout << "gcm 0 1 _ -> gcm 0 > 0 > _ ^" << endl;
    cout << "gcm 1 0 _ -> gcm 1 > 1 > _ ^" << endl;
    cout << "gcm 1 1 _ -> gcm 1 > 1 > _ ^" << endl;
    cout << "gcm 0 _ _ -> gcm 0 > 0 > _ ^" << endl;
    cout << "gcm 1 _ _ -> gcm 1 > 1 > _ ^" << endl;
    cout << "gcm | _ _ -> rtsst | > _ < _ ^" << endl;
    cout << "gcm 2 _ _ -> rtsstclstrtsft 2 < _ < _ ^" << endl; // rtsstclstrtsft - return to start second tape, clean second tape, return to start first tape

    cout << "ls 0 0 0 -> ls 0 > 0 ^ _ >" << endl;
    cout << "ls 0 0 1 -> ls 1 > 0 ^ _ >" << endl;
    cout << "ls 0 1 0 -> ls 0 > 1 ^ _ >" << endl;
    cout << "ls 0 1 1 -> ls 1 > 1 ^ _ >" << endl;
    cout << "ls 1 0 0 -> ls 0 > 0 ^ _ >" << endl;
    cout << "ls 1 0 1 -> ls 1 > 0 ^ _ >" << endl;
    cout << "ls 1 1 0 -> ls 0 > 1 ^ _ >" << endl;
    cout << "ls 1 1 1 -> ls 1 > 1 ^ _ >" << endl;
    cout << "ls 0 0 _ -> w2t | > 0 ^ _ ^" << endl; // w2t - write to fitst tape from second tape
    cout << "ls 0 1 _ -> w2t | > 1 ^ _ ^" << endl;
    cout << "ls 1 0 _ -> w2t | > 0 ^ _ ^" << endl;
    cout << "ls 1 1 _ -> w2t | > 1 ^ _ ^" << endl;
    cout << "ls | 0 _ -> w2t | > 0 ^ _ ^" << endl;
    cout << "ls | 1 _ -> w2t | > 1 ^ _ ^" << endl;

    cout << "w2t 0 0 _ -> w2t 0 > 0 > _ ^" << endl;
    cout << "w2t 0 1 _ -> w2t 1 > 1 > _ ^" << endl;
    cout << "w2t 1 0 _ -> w2t 0 > 0 > _ ^" << endl;
    cout << "w2t 1 1 _ -> w2t 1 > 1 > _ ^" << endl;
    cout << "w2t | 0 _ -> w2t 0 > 0 > _ ^" << endl;
    cout << "w2t | 1 _ -> w2t 1 > 1 > _ ^" << endl;
    cout << "w2t | _ _ -> rtsst | > _ < _ ^" << endl;
    cout << "w2t 2 _ _ -> rtsstclstrtsft 2 < _ < _ ^" << endl;

    cout << "rtsstclstrtsft 0 0 _ -> rtsstclstrtsft 0 ^ _ < _ ^" << endl;
    cout << "rtsstclstrtsft 0 1 _ -> rtsstclstrtsft 0 ^ _ < _ ^" << endl;
    cout << "rtsstclstrtsft 1 0 _ -> rtsstclstrtsft 1 ^ _ < _ ^" << endl;
    cout << "rtsstclstrtsft 1 1 _ -> rtsstclstrtsft 1 ^ _ < _ ^" << endl;
    cout << "rtsstclstrtsft 0 _ _ -> rsft2 0 ^ _ ^ _ ^" << endl; // rsft2 - return to start of first tape, write 2 after the first number
    cout << "rtsstclstrtsft 1 _ _ -> rsft2 1 ^ _ ^ _ ^" << endl;

    cout << "rsft2 0 _ _ -> rsft2 0 < _ ^ _ ^" << endl;
    cout << "rsft2 1 _ _ -> rsft2 1 < _ ^ _ ^" << endl;
    cout << "rsft2 | _ _ -> rtsft 2 < _ ^ _ ^" << endl; // rtsft - return to start of first tape
    cout << "rsft2 _ _ _ -> dc2w| _ > _ ^ _ ^" << endl; // dc2w| - done, change 2 with |

    cout << "rtsft 0 _ _ -> rtsft 0 < _ ^ _ ^" << endl;
    cout << "rtsft 1 _ _ -> rtsft 1 < _ ^ _ ^" << endl;
    cout << "rtsft | _ _ -> rtsft | < _ ^ _ ^" << endl;
    cout << "rtsft _ _ _ -> s1 _ > _ ^ _ ^" << endl;

    cout << "dc2w| 0 _ _ -> dc2w| 0 > _ ^ _ ^" << endl;
    cout << "dc2w| 1 _ _ -> dc2w| 1 > _ ^ _ ^" << endl;
    cout << "dc2w| 2 _ _ -> dc2w| | > _ ^ _ ^" << endl;
    cout << "dc2w| _ _ _ -> cl| _ < _ ^ _ ^" << endl; // cfl| - change last |

    cout << "cl| | _ _ -> gtsga _ < _ ^ _ ^" << endl; // gtsga - go to start and get answer

    cout << "gtsga 0 _ _ -> gtsga 0 < _ ^ _ ^" << endl;
    cout << "gtsga 1 _ _ -> gtsga 1 < _ ^ _ ^" << endl;
    cout << "gtsga | _ _ -> gtsga | < _ ^ _ ^" << endl;
    cout << "gtsga _ _ _ -> AC _ > _ ^ _ ^" << endl;

    return 0;
}