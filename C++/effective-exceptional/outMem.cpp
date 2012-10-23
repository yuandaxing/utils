/*
 * =====================================================================================
 *
 *       Filename:  outMem.cpp
 *
 *    Description:  to demenstrate oom
 *
 *        Version:  1.0
 *        Created:  2012年05月03日 17时11分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yuan DaXing (http://hi.baidu.com/%E8%A2%81%E5%A4%A7%E6%98%9F/home), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <memory>
#include <iostream>


void outOfMem() {
	std::cerr << "unable to satisfy request for memory\n";
	std::abort();
}

int main()
{
	const unsigned long oom = 1000000000L;
	std::set_new_handler(outOfMem);
	int * big = new int[oom];
	return 0;
}
