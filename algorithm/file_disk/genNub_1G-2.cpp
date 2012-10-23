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
#include <set>
#include "random.h"
#include "stdlib.h"
#include "MergeFileList.h"

const unsigned int G1 = 1024 * 1024 * 1024;
const unsigned int nNum = G1 / 100 ;
int main ( int argc, char *argv[] )
{
	std::multiset<int> msi;
	time_t cur = time(0);
	FILE *out[NFile];
	for(int i = 0; i < NFile; i++) {
		out[i] = fopen(fileList[i], "wa"); 
		if ( out[i] == NULL ) {
			fprintf(stderr, "cannot open file");
			abort();
		}
	}

	leveldb::Random_Level rand(cur);
	int i = 0;
	for ( i = 0; static_cast<unsigned>(i) < nNum; i += 1 ) {
		msi.insert(rand.Next());
	}

	for(int i = 0; i < NFile; i++) {
		for(auto iter = msi.begin(); iter != msi.end(); iter++) {
			fprintf(out[i], "%u ", *iter);
		}
		fclose(out[i]);
	}

	return 0;
}				/* ----------  end of function main  ---------- */
