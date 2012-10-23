/*
 * =====================================================================================
 *
 *       Filename:  testQueue.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年05月17日 22时50分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <Queue.h>
#include <time.h>
#include <ThreadService.h>
#include <assert.h>

threadSafe::BlockingQueue<int> bq;
threadSafe::BoundedQueue<int, 2>  boundedq;
const int onceSize = 10;
void* f1(void *)
{
	for(int i = 0; i < onceSize; i++) {
		bq.put(i);
		sleep(1);
	}
}

void* f2(void *)
{
	for(int i = 0; i < onceSize; i++) {
		int k = bq.get();
		assert(k == i);
	}
}

void * f3(void *)
{
	for(int i = 0; i < onceSize; i++) {
		boundedq.put(i);
	}

	assert(boundedq.size() == 2);
	sleep(1);
	for(int i = 0; i < onceSize; i++) {
		boundedq.put(i);
		sleep(1);
	}
}

void* f4(void *)
{
	for(int i = 0; i < onceSize; i++) {
		assert(boundedq.get() == i);
		sleep(1);
	}
	for(int i = 0; i < onceSize; i++){
		assert(boundedq.get() == i);
	}
}


int main() 
{
	typedef threadSafe::SimpleThread Thread;
	Thread t1(f1), t2(f2);

	t1.start();
	t2.start();

	Thread t3(f3), t4(f4);
	t3.start(), t4.start();

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	printf("thread safe queue succeed\n");
	return 0;
}
