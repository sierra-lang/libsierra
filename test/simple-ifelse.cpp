#include "sierra/defines.h"

int main() {
    int varying(4) a = {0, 1, 2, 3};
    int varying(4) b = 2;

    if (a < b)
        a = a - 1;
    else
        a = a + 1;
}
