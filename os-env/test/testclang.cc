/*
 * =====================================================================================
 *
 *       Filename:  testclang.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年06月21日 18时46分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>

	int
main ( int argc, char *argv[] )
{
	std::string str;
	str.push_back('c');
	str.append("test");
	std::cout << str ;
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
