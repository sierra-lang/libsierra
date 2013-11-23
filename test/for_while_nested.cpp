#include "sierra.h"

using namespace sierra;

int main(int argc, char** argv)
{
    int j = 1;
    for (int varying(4) i = seq<4>(); i < argc; i++)
    {
        if (i > 42) {
            while (j != i)
                ++j;
        }
    }
    return j;
}
