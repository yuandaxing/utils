/*
 * =====================================================================================
 *
 *       Filename:  testTime.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年06月11日 21时19分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <time_internal.h>
#include <stdint.h>

	int
main ( int argc, char *argv[] )
{
	using namespace Time;
	uint64_t t = CurMillSec();

	printf("%llu\n", t);
	printf("%llu\n", CurMillSecAfterKMillSec(1000));
	printf("%llu\n", CurMillSecAfterKSec(2));
	printf("%u\n", CurSec());
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
