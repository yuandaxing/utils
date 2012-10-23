/*
 * =====================================================================================
 *
 *       Filename:  testProgress.cc
 *
 *    Description:  test boost class
 *
 *        Version:  1.0
 *        Created:  2012年05月25日 20时12分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <boost/progress.hpp>
#include <time.h>
#include <stdio.h>
int main ( ) {
	{
		boost::progress_timer t;
		boost::timer tx;
		sleep(5);
		std::cout << tx.elapsed() << std::endl;
	}

	{
		   boost::progress_timer j;  // start timing
		   sleep(5);
	}

	{
		boost::progress_display pd(13);
		for(int i = 0; i < 13; i++) {
			sleep(1);
			++pd;
		}
	}
}
