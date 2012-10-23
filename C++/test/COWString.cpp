/*
 * =====================================================================================
 *
 *       Filename:  COWString.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年09月26日 15时59分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <string>
#include <iostream>
//race danger must avoid
int main(int argc, char *argv[])
{
	std::string str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	std::string str1 = str;

	std::cout << (str.data() == str1.data()) << std::endl;

	str1.append("A");
	std::cout << (str.data() == str1.data()) << std::endl;
	return 0;
}
