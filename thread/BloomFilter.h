/*
 * =====================================================================================
 *
 *       Filename:  BloomFilter.h
 *
 *    Description:  a BloomFilter, the user must calculate the number of keys and add that many
 *    keys exactly.
 *
 *        Version:  1.0
 *        Created:  2012年05月21日 20时11分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
/*-----------------------------------------------------------------------------
 *  bloomfilter contains three key points, K, the number of hash functions per key;
 *  m, the number of bits; and n the key num.
 *  there are two way to implement bloomfilter. one is implement, for example cassandra
 *  https://github.com/yuandaxing/JavaUtils/blob/master/cgcl/data/structure/BloomFilter.java 
 *  and it use a table to calculate the K, and m, 
 *  http://pages.cs.wisc.edu/~cao/papers/summary-cache/node8.html
 *  another way is just use http://blog.csdn.net/jiaomeng/article/details/1495500
 *  to calculate K and m.
 *  and here we use the second method.
 *-----------------------------------------------------------------------------*/

#ifndef  _BLOOMFILTER_H_INC
#define  _BLOOMFILTER_H_INC
#include <math.h>
#include <string.h>
#include <boost/dynamic_bitset.hpp>
#include <new>
#include <DoubleMurmur.h>
#include <Logger.h>

namespace threadSafe{
class BloomFilter{
	public:
		explicit BloomFilter ( uint64_t nkey, 
				double falseProbability = 0.00001 )
	   		: bit_array ( NULL ) , M ( 0 ) {
			assert(nkey > 0);
			assert(falseProbability > 0 && falseProbability < 1);

			uint64_t m = static_cast<uint64_t> (nkey * log10(E) * 
					log10(1 / falseProbability) / log10(2) / log10(2));

			assert(m > 0);
			m = (m / 8 + 1) * 8;
			if(m > max_bits){
				fprintf(stderr, "%llu bits is to many\n", m);
				throw std::bad_alloc();
			}
			K = static_cast<uint64_t>(log(2.0) * m / nkey);

			DEBUG << "K:" << K << "\n" ;
			DEBUG << "M:" << ( m / 8 / 1000000 ) << "M\n" ;
			M = m;
			bit_array = new char [ M / 8 ];
			memset ( bit_array, 0, M / 8 );
		}

		~ BloomFilter ( ) {
			if ( bit_array )
				delete bit_array ;
		}

		void addKey(const char *key, size_t len) {
			DoubleMurmur dmm(key, len);
			for(int i = 0; i < K; i++) {
				int bit = dmm.next() % M ;
				bit_array [ bit / 8 ] |= 1 << ( bit % 8 ) ; 
			}
		}

		void addKey(const std::string &key) {
			addKey(key.c_str(), key.size());	
		}

		bool isIn(const char *key, size_t len) {
			DoubleMurmur dmm(key, len);
			for(int i = 0; i < K; i++) {
				int bit = dmm.next() % M ;
				if( ( bit_array[ bit / 8 ] & ( 
							1 << ( bit % 8 ) ) ) == 0 )
					return false;
			}
			return true;
		}

		bool isIn(const std::string &key){
			return isIn(key.c_str(), key.size());
		}

	private:
		uint64_t K;
		uint64_t M;
		char *bit_array;
		/*-----------------------------------------------------------------------------
		 *  because bit_array implement is like deque, it random access is not very
		 *  effecient, i just use char * to implement bit array
		 *	boost::dynamic_bitset<> bit_array;
		 *-----------------------------------------------------------------------------*/
		static const uint64_t max_bits;
		static const double	E;
};
const uint64_t BloomFilter::max_bits = (static_cast<uint64_t>(1) << 30) * 8;
const  double BloomFilter::E = 2.71828182845904523536;
}
#endif   /* ----- #ifndef _BLOOMFILTER_H_INC  ----- */
