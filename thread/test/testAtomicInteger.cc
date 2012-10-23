/*
 * =====================================================================================
 *
 *       Filename:  testAtomicInteger.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年05月19日 19时01分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <AtomicInteger.h>
#include <assert.h>

int main()
{
	threadSafe::S32AtomicInteger s32;
	assert(s32.get() == 0);
	assert(s32.getAndAdd(1) == 0);
	assert(s32.addAndGet(1) == 2);
	assert(s32.get() == 2);

	assert(s32.getAndSub(1) == 2);
	assert(s32.subAndGet(1) == 0);
	
	s32.add(100);
	assert(s32.get() == 100);
	assert(s32.incrAndGet() == 101);
	assert(s32.getAndIncr() == 101);

	assert(s32.getAndDecr() == 102);
	assert(s32.decrAndGet() == 100);

	s32.sub(100);
	assert(s32.get() == 0);

	assert(s32.getAndSet(100) == 0);
	assert(s32.get() == 100);


	fprintf(stderr, "pass all test\n");
	return 0;
}
