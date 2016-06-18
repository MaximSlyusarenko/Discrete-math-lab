#include <iostream>

using namespace std;

int main()
{
    freopen ("factorial.out", "w", stdout);

    cout << "start: s" << endl;
    cout << "accept: ac" << endl;
    cout << "reject: rj" << endl;
    cout << "blank: _" << endl;

    cout << "s 1 -> w3 1 <" << endl; // w3 - write 3

    cout << "w3 _ -> s1 3 >" << endl; // s1 - start 1

    cout << "s1 1 -> ge 1 >" << endl; // ge - go to the end

    cout << "ge 0 -> ge 0 >" << endl;
    cout << "ge 1 -> ge 1 >" << endl;
    cout << "ge _ -> cp _ <" << endl; // cp - copy

    cout << "cp 1 -> cp1 2 <" << endl; // cp1 - copy 1
    cout << "cp 0 -> cp0 2 <" << endl; // cp0 - copy 0

    cout << "cp1 0 -> cp1 0 <" << endl;
    cout << "cp1 1 -> cp1 1 <" << endl;
    cout << "cp1 3 -> cp1 3 <" << endl;
    cout << "cp1 _ -> g2r1 1 >" << endl; // g2r1 - go to 2, restore 1

    cout << "cp0 0 -> cp0 0 <" << endl;
    cout << "cp0 1 -> cp0 1 <" << endl;
    cout << "cp0 3 -> cp0 3 <" << endl;
    cout << "cp0 _ -> g2r0 0 >" << endl; // g2r0 - go to 2, restore 0

    cout << "g2r1 0 -> g2r1 0 >" << endl;
    cout << "g2r1 1 -> g2r1 1 >" << endl;
    cout << "g2r1 3 -> g2r1 3 >" << endl;
    cout << "g2r1 2 -> cp 1 <" << endl;

    cout << "g2r0 0 -> g2r0 0 >" << endl;
    cout << "g2r0 1 -> g2r0 1 >" << endl;
    cout << "g2r0 3 -> g2r0 3 >" << endl;
    cout << "g2r0 2 -> cp 0 <" << endl;

    cout << "cp 3 -> cds1 3 <" << endl; // cds1 - copy done, subtract 1

    cout << "cds1 0 -> cds1 1 <" << endl;
    cout << "cds1 1 -> s1dclz 0 <" << endl; // s1dclz - subtract 1 done, check leading zeros

    cout << "s1dclz 0 -> s1dclz _ >" << endl;
    cout << "s1dclz 1 -> gescm 1 >" << endl; // gescm - go to the end of second number (n - k) and continue multiplication

    cout << "s1dclz 3 -> ac _ >" << endl; // done

    cout << "gescm 0 -> gescm 0 >" << endl;
    cout << "gescm 1 -> gescm 1 >" << endl;
    cout << "gescm 3 -> mbf1 3 <" << endl; // mbf1 - multiplication, before first 1

    cout << "mbf1 0 -> gefw0b 2 >" << endl; // gefw0b - go to the end of first number and write 0, before first 1
    cout << "mbf1 1 -> maf1 1 <" << endl; // maf1 - multiplication, after first 1 TODO written below

    cout << "gefw0b 0 -> gefw0b 0 >" << endl;
    cout << "gefw0b 1 -> gefw0b 1 >" << endl;
    cout << "gefw0b 3 -> gefw0b 3 >" << endl;
    cout << "gefw0b _ -> r2r0b 0 <" << endl; // r2r0b - return to 2, restore 0, before first 1

    cout << "r2r0b 0 -> r2r0b 0 <" << endl;
    cout << "r2r0b 1 -> r2r0b 1 <" << endl;
    cout << "r2r0b 3 -> r2r0b 3 <" << endl;
    cout << "r2r0b 2 -> mbf1 0 <" << endl;

    // TODO: maf1 должно по 0 писать 0 к концу предыдущего слова, но при этом важно будет знать количество дописанных нулей между двумя соседними единицами, так что надо, чтобы оно писало в конец первого числа 4, потом 0 и, когда вернется к текущему разряду второго числа, переходила в maf0af1 - multiplication, after first 0 after first 1, которое не пишет 4, а просто пишет 0, но при попадании на следующую единицу, надо провести операции с ней и снова вернуться в maf1, потому что нам снова нужно знать, сколько нулей между единицами

    cout << "maf1 0 -> gefw40 2 >" << endl; // gefw40 - go to the end of first number and write 40
    // TODO: maf1 1 - дописать к первому слову 40 и прибавить после этого его старое к нему новому, забив на 4, после чего нужно убрать 4 и сдвинуть на 1 все, что написано за ней

    cout << "gefw40 0 -> gefw40 0 >" << endl;
    cout << "gefw40 1 -> gefw40 1 >" << endl;
    cout << "gefw40 3 -> gefw40 3 >" << endl;
    cout << "gefw40 _ -> w0 4 >" << endl; // w0 - write 0

    cout << "w0 _ -> r2r0maf0af1 0 <" << endl; // r2r0maf0af1 - go to 2, restore 0 and move to state maf0af1

    cout << "r2r0maf0af1 0 -> r2r0maf0af1 0 <" << endl;
    cout << "r2r0maf0af1 1 -> r2r0maf0af1 1 <" << endl;
    cout << "r2r0maf0af1 3 -> r2r0maf0af1 3 <" << endl;
    cout << "r2r0maf0af1 4 -> r2r0maf0af1 4 <" << endl;
    cout << "r2r0maf0af1 2 -> maf0af1 0 <" << endl; // maf0af1 - multiplication, after first 0 after first 1

    cout << "maf0af1 0 -> gefwo0 2 >" << endl; // gefwo0 - go to the end of first, write only 0 TODO
    cout << "maf0af1 1 -> gefw0a 2 >" << endl; // gefw0a - go to the end of first, write 0 and add TODO
    // TODO: maf0af1 1 - дописать к первому слову 0 и прибавить после этого его старое к нему новому, забив на 4, после чего нужно убрать 4 и сдвинуть на 1 все, что написано за ней



    return 0;
}