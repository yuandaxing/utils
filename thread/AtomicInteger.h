/*
 * =====================================================================================
 *
 *       Filename:  AtomicInteger.h
 *
 *    Description:  I implement a lock free AtomicInteger class , use the gcc built in atomic function
 *    type __sync_fetch_and_add (type *ptr, type value, ...)
 *    type __sync_fetch_and_sub (type *ptr, type value, ...)
 *    type __sync_fetch_and_or (type *ptr, type value, ...)
 *    type __sync_fetch_and_and (type *ptr, type value, ...)
 *    type __sync_fetch_and_xor (type *ptr, type value, ...)
 *    type __sync_fetch_and_nand (type *ptr, type value, ...)
 *    type __sync_add_and_fetch (type *ptr, type value, ...)
 *    type __sync_sub_and_fetch (type *ptr, type value, ...)
 *    type __sync_or_and_fetch (type *ptr, type value, ...)
 *    type __sync_and_and_fetch (type *ptr, type value, ...)
 *    type __sync_xor_and_fetch (type *ptr, type value, ...)
 *    type __sync_nand_and_fetch (type *ptr, type value, ...)
 *
 *        Version:  1.0
 *        Created:  2012年05月19日 18时23分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  _ATOMICINTEGER_H_INC
#define  _ATOMICINTEGER_H_INC
#include <boost/noncopyable.hpp>
#include <stdint.h>
/*-----------------------------------------------------------------------------
 *  we donnot support operator= and copy constructor, because this dosenot behaive
 *  atomic
 *-----------------------------------------------------------------------------*/
namespace threadSafe{
template <typename T>
class AtomicInteger: private boost::noncopyable {
	private:
		volatile T value;

	public:
		explicit AtomicInteger(const T &v = 0):
			value(v) { }
		~AtomicInteger() { }

		T getAndAdd(const T &v) {
			return __sync_fetch_and_add(&value, v);
		}

		T addAndGet(const T &v) {
			return getAndAdd(v) + v;
		}

		T get() {
			return getAndAdd(0);
		}

		T getAndSub(const T &v) {
			return getAndAdd(-v);
		}

		T subAndGet(const T &v) {
			return getAndSub(v) - v;
		}

		void add(const T &v) {
			getAndAdd(v);
		}

		void sub(const T &v) {
			getAndSub(v);
		}
		
		T getAndIncr() {
			return getAndAdd(1);
		}

		T getAndDecr() {
			return getAndSub(1);
		}

		T decrAndGet() {
			return subAndGet(1);
		}

		T incrAndGet() {
			return addAndGet(1);
		}

		T getAndSet(const T &v) {
			return __sync_lock_test_and_set(&value, v);
		}
};

typedef AtomicInteger<uint32_t> U32AtomicInteger;
typedef AtomicInteger<uint64_t> U64AtomicInteger;
typedef AtomicInteger<int32_t>  S32AtomicInteger;
typedef AtomicInteger<int64_t>  S64AtomicInteger;
}
#endif   /* ----- #ifndef _ATOMICINTEGER_H_INC  ----- */
