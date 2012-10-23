/*
 * =====================================================================================
 *
 *       Filename:  testCoding.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年06月05日 22时04分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <coding.h>
#include <string>
#include <assert.h>

int
main ( int argc, char *argv[] )
{
	const int n = 100;
	int i;	
	std::string int_str;

	using namespace leveldb;
	for ( i = n-1; i >= 0; i -= 1 ) {
		PutFixed32 (&int_str, i) ;
	}
	assert(int_str.size() == 4 * n );
	
	const char *p = int_str.data();

	for ( i = n-1; i >= 0; i -= 1 ) {
		assert(DecodeFixed32(p) == i);
		p += 4;
	}

	int_str.clear();
	for ( i = n-1; i >= 0; i -= 1 ) {
		PutFixed64(&int_str, i);
	}

	p = int_str.data();
	for ( i = n-1; i >= 0; i -= 1 ) {
		assert(DecodeFixed64(p) == i);
		p += 8;
	}

	int_str.clear();
	for ( i = n-1; i >= 0; i -= 1 ) {
		PutVarint32(&int_str, i);
	}

	p = int_str.data();
	const char *end = p + int_str.size();
	for ( i = n-1; i >= 0; i -= 1 ) {
		uint32_t v;
		p = GetVarint32Ptr(p, end, &v);
		assert(p != NULL && v == i);
	}


	int_str.clear();
	for ( i = n-1; i >= 0; i -= 1 ) {
		PutVarint64(&int_str, i);
	}

	p = int_str.data();
	end = p + int_str.size();
	for ( i = n-1; i >= 0; i -= 1 ) {
		uint64_t v;
		p = GetVarint64Ptr(p, end, &v);
		assert(p != NULL && v == i);
	}

	uint32_t z = 1234, v;
	int_str.clear();
	PutVarint32(&int_str, z);
	Slice s(int_str);
	assert(GetVarint32(&s, &v));
	assert(v == z);


	uint64_t z64 = 1234, v64;
	int_str.clear();
	PutVarint64(&int_str, z64);
	Slice s64(int_str);
	assert(GetVarint64(&s64, &v64));
	assert(v64 == z64);

	int_str.clear();
	const char *str = "what's is the fuck\n";
	Slice sstr(str);
	PutLengthPrefixedSlice(&int_str, sstr);
	Slice t, sf(int_str);
	assert(GetLengthPrefixedSlice(&sf, &t));
	assert(t.size() == strlen(str));
	return EXIT_SUCCESS;
}				/* ----------  end of function ain  ---------- */
