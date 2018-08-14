#include "sierra/defines.h"
#include "test.h"


spmd(4) int varying(4) store( bool &b ) {
    int varying(4) g = 0;
    if ( b )
        g = 1;
    return g;
}

int main() {
    bool varying(4) b = { true, true, false, false };
    int varying(4) g = store( b );
    return unify( g, 1, 1, 0, 0 );
}

// $RESULT: 15
