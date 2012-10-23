/*
 * =====================================================================================
 *
 *       Filename:  DoubleMurMur.h
 *
 *    Description:  use double murmur hash 
 *
 *        Version:  1.0
 *        Created:  2012年05月21日 21时43分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  _DOUBLEMURMUR_H_INC
#define  _DOUBLEMURMUR_H_INC
#include <hash.h>
#include <string.h>

using namespace leveldb ;
class DoubleMurmur{
	private:
		uint32_t first, second;
		int cur;

	public:
		DoubleMurmur(const char *data, int len):
			first(0), second(0), cur(0) {
				first = Hash ( data, len, 0 ) ;
				second = Hash ( data, len, first ) ;
			}

		uint32_t next() {
			cur++;
			return first + second * cur;
		}
};
#endif   /* ----- #ifndef _DOUBLEMURMUR_H_INC  ----- */
