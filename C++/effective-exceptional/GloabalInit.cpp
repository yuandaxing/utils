/*
 * =====================================================================================
 *
 *       Filename:  GloabalInit.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月01日 09时11分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>

extern int j, x;
int i = j + 10 + x;
int j = 20;
int x = 50;

int main(int argc, char *argv[])
{
	std::cout << "i:" << i << " j:" << j << std::endl;
	return 0;
}
