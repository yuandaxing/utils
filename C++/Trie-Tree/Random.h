/*
 * =====================================================================================
 *
 *       Filename:  Random.h
 *
 *    Description:  rand string, digitstring and so on
 *
 *        Version:  1.0
 *        Created:  2012年05月23日 23时08分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef  _RANDOM_H_INC
#define  _RANDOM_H_INC
#include <string>
#include <string.h>
#include <time.h>
using std::string;
namespace threadSafe{
class Random{
	public:
		static void seed() {
			srand(time(NULL));
		}

		static string getRandString(const string &str, int len) {
			string tmp(len, '0');
			for(int i = 0; i < len; i++) {
				tmp[i] = str[rand() % str.size()];
			}
			return tmp;
		}

		static string getRandString(int len) {
			return getRandString(chs, len);
		}

		static string getRandDigitString(int len) {
			return getRandString(digit_chs, len);
		}


		/*-----------------------------------------------------------------------------
		 *  actually it is not  that fast
		 *-----------------------------------------------------------------------------*/
		/* 
		static string getRandString_fast(const string &str, int len) {
			string tmp(len, '0');
			for(int i = 0; i < len; i++) {
				tmp[i] = str[random.Next() % str.size()];
			}
			return tmp;
		}

		static string getRandString_fast(int len) {
			return getRandString_fast(chs, len);
		}

		static string getRandDigitString_fast(int len) {
			return getRandString_fast(digit_chs, len);
		}

	private:
		static leveldb::Random_Level random;
		*/
	private:
		static const string chs;
		static const string digit_chs;
};
//leveldb::Random_Level Random::random( time(NULL) ) ;
const string Random::chs="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string Random::digit_chs="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

#endif   /* ----- #ifndef _RANDOM_H_INC  ----- */
