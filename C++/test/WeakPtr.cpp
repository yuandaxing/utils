/*
 * =====================================================================================
 *
 *       Filename:  WeakPtr.cpp
 *
 *    Description:  to domenstrate how to use weak pointer
 *
 *        Version:  1.0
 *        Created:  2012年09月20日 14时56分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include <iostream>
#include <cassert>

class A {};

int main() {

	boost::weak_ptr<A> w;
	assert(w.expired());
	{
		boost::shared_ptr<A> p(new A());
		assert(p.use_count()==1);
		w=p;
		assert(p.use_count()==w.use_count());
		assert(p.use_count()==1);

		// 从weak_ptr创建shared_ptr
		boost::shared_ptr<A> p2(w);
		assert(p2==p);
	}
	assert(w.expired());
	boost::shared_ptr<A> p3=w.lock();
	assert(!p3);
}
