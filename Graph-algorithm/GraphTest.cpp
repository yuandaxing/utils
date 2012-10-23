/*
 * =====================================================================================
 *
 *       Filename:  GraphTest.cpp
 *
 *    Description:  to test the Graph Creator
 *
 *        Version:  1.0
 *        Created:  2012年09月06日 23时20分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include "Graph.h"
#include <string>

int main(int argc, char *argv[])
{
	std::string filename = "Graph-1.txt";
	MatrixGraph mg(filename);
	std::cout << mg;
	mg.transpose();
	std::cout << mg;
	AdjacentGraph adjg(filename);
	std::cout << adjg;
	adjg.transpose();
	std::cout << adjg;
	return 0;
}
