/*
 * =====================================================================================
 *
 *       Filename:  testBloomFilter.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年05月23日 22时49分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <BloomFilter.h>
#include <stdint.h>
#include <Random.h>
#include <set>
#include <string>
#include <TestHelper.h>
#include <Logger.h>
const int nkey= 10000000;
int
main ( int argc, char *argv[] )
{
	using std::set;
	using std::string;
	using namespace threadSafe;

	set<string> key;

	Random::seed();
	Logger::init(Logger::LoggerLevel::DEBUG_);

	{
		fprintf(stderr, "generator %d keys of length 20\n", nkey);
		SimpleTimeCounter stc;
		while(key.size() < nkey) {
			key.insert(Random::getRandString(20));
		}
	}

	BloomFilter bf(key.size(), 0.001);

	
	{
		fprintf(stderr, "time to apply bf for %u keys 0f"
			   "length 20\n", key.size());

		SimpleTimeCounter stc;
		for(set<string>::iterator iter = key.begin(); 
				iter != key.end(); ++iter) {
			bf.addKey(*iter);
		}
	}

	{
		fprintf(stderr, "the keys must be in the bloomfiter\n");
		SimpleTimeCounter stc;

		for ( set<string>::iterator iter = key.begin() ; 
				iter != key.end() ; ++iter ) {
			assert ( bf.isIn( *iter ) == true );
		}
	}

  	{
		using namespace leveldb ;
		fprintf(stderr, "\ntest murmur hashing\n");
		SimpleTimeCounter stc;
		for ( set<string>::iterator iter = key.begin() ; 
				iter != key.end() ; ++iter ) {
			uint32_t v;
			v = Hash( iter->c_str(), iter->size(), 0 ) ;
		}
	}

	{
		fprintf(stderr, "test for err probability\n");

		SimpleTimeCounter stc;
		int count = 0, falseC = 0;

		for(int i = 0; i < nkey; i++) {
			string test = Random::getRandString(20);
			if( key.find(test) == key.end() ) {
				count++ ;
				if ( bf.isIn(test) == true ) 
					falseC++ ;
			}
		}

		fprintf( stderr, "%d keys and %d false\n", count
				, falseC );
		fprintf(stderr, " err probability %lf\n",
				static_cast<double> ( falseC ) / count );
	}


	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
