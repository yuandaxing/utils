/*
 * =====================================================================================
 *
 *       Filename:  testLogging.cc
 *
 *    Description:  test the log defines, hard to understand
 *
 *        Version:  1.0
 *        Created:  2012年05月20日 15时31分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <Logger.h>
#include <ThreadService.h>

using namespace threadSafe;
void logFunc(int &T) {
	for(int i = 0; i < T; i++) {
		WARN << "fuck " << i << " \n";
	}
}

int main()
{
	using namespace threadSafe;
	Logger::init(Logger::LoggerLevel::INFO_, "test.log");

	ThreadPoolWorker<int> tpw(10);
	tpw.start();
	for(int i = 0; i < 100; i++) {
		tpw.putWork(Work<int>::getWork(i+100, logFunc));
	}
	sleep(30);
	Logger::flush();
	tpw.stop();
	return 0;
}


