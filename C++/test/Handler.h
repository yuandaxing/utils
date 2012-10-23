/*
 * =====================================================================================
 *
 *       Filename:  Handler.h
 *
 *    Description:  to hold something
 *
 *        Version:  1.0
 *        Created:  2012年09月13日 23时01分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  HANDLER_H__INC
#define  HANDLER_H__INC
#include <iostream>
template<typename T>
class Handler {
	public:
		Handler(T *t): count_(new size_t(1)), t_(t) { }
		Handler(const Handler &h): count_(h.count_),
			t_(h.t_) { ++(*count_); }
		Handler & operator=(const Handler &h) {
			++(*h.count_); // allow h = h;
			decr_use();
			count_ = h.count_;
			t_ = h.t_;
			return *this;
		}
		~Handler() {
			decr_use();
		}

		T * getRaw() {
			return t_;
		}
		 
		T * operator->() {
			return t_;
		}
	private:
	size_t *count_;
	T *t_;

	void decr_use() {
		if( --(*count_) == 0 )
		{
			delete count_;
			delete t_;
		}
	}
};
#endif   /* ----- #ifndef HANDLER_H__INC  ----- */
