/*
 * =====================================================================================
 *
 *       Filename:  testCompile.cc
 *
 *    Description:  
 *
 *
 *        Version:  1.0
 *        Created:  2012年06月21日 19时49分31秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

class test{
	private:
		int i;
	public:
		test(const test &rhs) : i(rhs.i) { }
};


	int
main ( int argc, char *argv[] )
{
	test t;
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
