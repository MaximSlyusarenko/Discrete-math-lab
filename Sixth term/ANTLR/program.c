#include <stdio.h>

using namespace std;

int main() {
    int a = 5;
    if (a < 6) {
        a++;
    } else if (a == 6) {
        a--;
    } else {
        a = 2;
    }
    return 0;
}