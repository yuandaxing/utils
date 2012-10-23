/*
 * =====================================================================================
 *
 *       Filename:  Queue.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年05月17日 21时44分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  _QUEUE_H_INC
#define  _QUEUE_H_INC

#include <LockService.h>
#include <boost/noncopyable.hpp>
#include <list>

namespace threadSafe {

template<typename T>
class BlockingQueue: private boost::noncopyable{
	private:
		Mutex m;
		Condition notEmpty;
		std::list<T> list;

	public:
		BlockingQueue(): list(), m(), notEmpty(m) { }

		void put(const T &data) {
			MutexGuard mg(m);
			list.push_back(data);
			notEmpty.notify();
		}

		T get() {
			MutexGuard mg(m);
			while(list.empty())
				notEmpty.wait();
			T ret = list.front();
			list.pop_front();
			return ret;
		}

		size_t size() {
			MutexGuard mg(m);
			return list.size();
		}
};

template <typename T, int _size>
class BoundedQueue: boost::noncopyable {
		private:
			std::list<T> list;
			mutable Mutex m;
			mutable Condition notFull, notEmpty;

		public:
			BoundedQueue(): notFull(m), notEmpty(m) { }

			void put(const T &data) {
				MutexGuard mg(m);
				while(list.size() == _size)
					notFull.wait();
				list.push_back(data);
				notEmpty.notify();
			}

			T get() {
				MutexGuard mg(m);
				while(list.empty()) {
					notEmpty.wait();
				}
				T ret = list.front();
				list.pop_front();
				notFull.notify();
				return ret;
			}

			size_t size() const {
				MutexGuard mg(m);
				return list.size();
		}
};

}
#endif   /* ----- #ifndef _QUEUE_H_INC  ----- */
