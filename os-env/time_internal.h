/*
 * =====================================================================================
 *
 *       Filename:  Time.h
 *
 *    Description:  Time management
 *
 *        Version:  1.0
 *        Created:  2012年06月11日 20时04分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  _TIME_H_INC
#define  _TIME_H_INC
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
namespace Time{
const uint64_t MillPerSecond = 1000 * 1000;
uint64_t CurMillSec() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return static_cast<uint64_t>(tv.tv_sec) * MillPerSecond + tv.tv_usec;
}
uint64_t CurMillSecAfterKMillSec(uint64_t k) {
	return CurMillSec() + k;
}
uint64_t CurMillSecAfterKSec(uint32_t k) {
	return CurMillSecAfterKMillSec(k * MillPerSecond);
}
uint32_t CurSec() {
	return time(0);
}
}
#endif   /* ----- #ifndef _TIME_H_INC  ----- */
