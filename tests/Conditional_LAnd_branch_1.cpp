#include "sierra/defines.h"
#include "test.h"

int main()
{
	bool varying(4) a = {true, true, false, false};
	bool varying(4) b = {true, false, true, false};
	bool varying(4) c = {true, false, true, false};
	bool varying(4) d = {false, false, true, true};

	int varying(4) x = {0, 1, 2, 3};

	if ( ( a ? b : c ) && d )	// < F, F, T, F >
		++x;
	else
		--x;

	return unify( x, -1, 0, 3, 2 );
}

// $RESULT: 15
