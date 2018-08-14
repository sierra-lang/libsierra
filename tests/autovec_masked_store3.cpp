#include "sierra/defines.h"
#include "test.h"

int g = 0;

spmd(4)
void store( bool &b )
{
  if ( b )
    g = 1;
}

int main()
{
	bool varying(4) b = { true, true, false, false };
  store( b );


	return unify( g, 1, 1, 0, 0 );
}

// $RESULT: 15
