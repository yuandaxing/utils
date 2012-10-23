/*
 * =====================================================================================
 *
 *       Filename:  static.cpp
 *
 *    Description:  local static and non local static
 *
 *        Version:  1.0
 *        Created:  2012年05月02日 15时29分29秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yuan DaXing (http://hi.baidu.com/%E8%A2%81%E5%A4%A7%E6%98%9F/home), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <pthread.h>
#include <iostream>

extern int k;
int j = k;
int k = 10;
int b = k;
int & getk() {
	static int k = 10;
	return k;
}

int & getj() {
	static int j = getk();
	return j;
}

int & getb() {
	static int b = getk();
	return b;
}

pthread_once_t once = PTHREAD_ONCE_INIT;
void once_run(void)
{
	std::cout<<"once_run in thread "
		<<(unsigned int )pthread_self()<<std::endl;
}

void run() {
	pthread_once(&once, once_run);
	std::cout << "run" << std::endl;
}

int main()
{
	std::cout << "j:" << j << std::endl;
	std::cout << "k:" << k << std::endl;
	std::cout << "b:" << b << std::endl;
	std::cout << "getb()" << getb() << std::endl;

	for(int i = 0; i < 10; i++) {
		run();
	}

	return 0;
}
