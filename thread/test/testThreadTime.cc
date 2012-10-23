/*
 * =====================================================================================
 *
 *       Filename:  testThreadTime.c
 *
 *    Description:  use multithread to test time function
 *
 *        Version:  1.0
 *        Created:  2012年05月19日 16时19分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <time.h>
#include <ThreadService.h>

void func(int &t) {
	for(int i = 0; i < t; i++) {
		time_t cur = time(0);
		fprintf(stderr, "%lu\n", cur);
		fprintf(stderr, "%s\n", ctime(&cur));
	}
}

const int nT = 20;
const int works = 1000;
int main()
{
	using threadSafe::ThreadPoolWorker;
	using threadSafe::Work;
	ThreadPoolWorker<int> threads(20);
	for(int i = 0; i < works; i++) {
		threads.putWork(Work<int>::getWork(i + 1000, func));
	}
	threads.start();
	sleep(100);
	return 0;
}
