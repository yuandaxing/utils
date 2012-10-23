/*
 * =====================================================================================
 *
 *       Filename:  testSpeed.cc
 *
 *    Description:  
 *
 *
 *        Version:  1.0
 *        Created:  2012年05月24日 21时38分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <TestHelper.h>

	int
main ( int argc, char *argv[] )
{
	using namespace threadSafe;
	const int c = 100000000;
	{
		SimpleTimeCounter stc;
		int i = 0;
		while(i++ < c) ;
		fprintf(stderr, "%d", i);
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
