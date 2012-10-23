/*
 * =====================================================================================
 *
 *       Filename:  test1DoubleHash.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年05月21日 21时59分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <DoubleMurmur.h>
#include <stdio.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	const char *test1 = "what is the fuck";
	const int len = strlen(test1);

	DoubleMurmur test(test1, len);

	for(int i = 0; i < 10; i++) {
		printf("%u ", test.next());
	}
	printf("\n");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
