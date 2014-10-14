#ifndef TEST_H
#define TEST_H

#include "sierra/defines.h"

template< typename T >
int length( T ){ return 1; }

template< typename T, typename... Args >
int length( T, Args... args ){ return length( args... ) + 1; }

/* Matches the elements of the vector with the following arguments.
 * Returns a bit-vector with 1 bit for each vector element.  The bit is set to 1
 * iff comparison succeeded.
 */
template< class T, int N, typename... Args >
int unify( T varying(N) &v, Args... args )
{
	if ( length( args... ) != N ) return -1;

	int *vp = (int *) &v;
	int res = 0;
	T arr[] = {args...};
	for ( int i = 0; i < N; ++i )
		res |= (vp[i] == arr[i]) << i;
	return res;
}

#endif
