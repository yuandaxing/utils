/*
 * =====================================================================================
 *
 *       Filename:  ref-pointer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年04月26日 08时43分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yuan DaXing (http://hi.baidu.com/%E8%A2%81%E5%A4%A7%E6%98%9F/home), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
#include <string>


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	using std::string;
	string s1 = "chenhui";
	string s2 = "ydx";
	const string &rs3 = s1 + s2;
	//string &rs4 = s1 + s2;
	//string *p = &(s1 + s2);

	//const int *p1 = 3;
	std::cout << rs3;

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
