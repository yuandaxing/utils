/*
 * =====================================================================================
 *
 *       Filename:  genNub_1G.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年07月06日 19时18分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <time.h>
#include <stdio.h>
#include <string>
#include "random.h"
#include "stdlib.h"

const unsigned int G1 = 1024 * 1024 * 1024;
const unsigned int nNum = G1 / 2;
int main ( int argc, char *argv[] )
{
	const std::string file = "test.txt";
	time_t cur = time(0);
	FILE *out = fopen(file.c_str(), "wa"); 
	if ( out == NULL ) {
		fprintf(stderr, "cannot open file");
		abort();
	}

	leveldb::Random_Level rand(cur);
	int i = 0;
	for ( i = 0; static_cast<unsigned>(i) < nNum; i += 1 ) {
		fprintf(out, "%u ", rand.Next());
	}
	fclose(out);

	return 0;
}				/* ----------  end of function main  ---------- */
