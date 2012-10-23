/*
 * =====================================================================================
 *
 *       Filename:  Primitive.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月03日 15时45分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
int main(int argc, char *argv[])
{
	int *i = new int;
	float *f = new float;
	char *c = new char;
	std::cout << *i << std::endl;
	std::cout << *f << std::endl;
	std::cout << static_cast<int>(*c) << std::endl;
	
	return 0;

}
