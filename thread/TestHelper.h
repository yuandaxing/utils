/*
 * =====================================================================================
 *
 *       Filename:  TestHelper.h
 *
 *    Description:  I want this class to accelerate your test
 *
 *        Version:  1.0
 *        Created:  2012年05月24日 20时21分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

/*-----------------------------------------------------------------------------
 *  boost::progress_timer, boost::progress_display is more powerful and 
 *  good looking then i implement
 *-----------------------------------------------------------------------------*/

#ifndef  _TESTHELPER_H_INC
#define  _TESTHELPER_H_INC
#include <stdio.h>
#include <time.h>
namespace threadSafe {
class SimpleTimeCounter{
	private:
		time_t start;
	public:
		SimpleTimeCounter() {
			time(&start);
		}

		time_t elapse() {
			return time(0) - start;
		}

		~SimpleTimeCounter() {
			fprintf(stderr, "elapse %lu seconds\n", elapse());
		}
};
}
#endif   /* ----- #ifndef _TESTHELPER_H_INC  ----- */
