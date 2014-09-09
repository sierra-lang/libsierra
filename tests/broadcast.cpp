#include "sierra/defines.h"
#include "test.h"

int main()
{
	int varying(4) v = 42;

	return unify( v, 42, 42, 42, 42 );
}

// $RESULT: 15
