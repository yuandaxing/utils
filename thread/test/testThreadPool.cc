/*
 * =====================================================================================
 *
 *       Filename:  testThreadPool.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年05月19日 10时17分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <ThreadService.h>
#include <time.h>

void func(int &i) {
	int sum = 0;
	for(int j = 0; j < i; j++)
		sum += j;
	fprintf(stderr, "sum is %d\n", sum);
	fprintf(stderr, "pid id is %d\n", 
			threadSafe::ThreadUtils::pid());
	fprintf(stderr, "thread id is %lu\n", 
			threadSafe::ThreadUtils::thread_id());
}

using threadSafe::ThreadPoolWorker;
using threadSafe::Work;
const int works = 10000;
int main()
{
	ThreadPoolWorker<int> tp(10);
	tp.start();

	for(int i = 0; i < works; i++) {
		tp.putWork(Work<int>::getWork(i+100, func));
	}

	sleep(10);
	tp.stop();

}
