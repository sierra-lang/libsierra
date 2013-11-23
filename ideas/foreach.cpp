#include "sierra/sierra.h"

int main() {
    sierra::for_each(23, 42, [&] {
    });
}
