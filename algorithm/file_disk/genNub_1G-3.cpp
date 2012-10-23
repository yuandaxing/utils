/*
 * =====================================================================================
 *
 *       Filename:  genNub_1G-3.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月05日 15时02分03秒
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
#include "Random.h"
#include "stdlib.h"
#include "MergeFileList.h"

const unsigned int G1 = 1024 * 1024 * 1024;
const unsigned int nNum = G1 / 1000 ;
int main ( int argc, char *argv[] )
{
	std::multiset<Item, Compare> msi;
	FILE *out[NFile];
	for(int i = 0; i < NFile; i++) {
		out[i] = fopen(fileList[i], "w"); 
		if ( out[i] == NULL ) {
			fprintf(stderr, "cannot open file");
			abort();
		}
	}

	threadSafe::Random rand;
	rand.seed();
	int i = 0;
	for ( i = 0; static_cast<unsigned>(i) < nNum; i += 1 ) {
		msi.insert(Item(rand.getRandDigitString(10).c_str(),
					rand.getRandDigitString(10).c_str()));
	}

	for(int i = 0; i < NFile; i++) {
		for(auto iter = msi.begin(); iter != msi.end(); iter++) {
			fprintf(out[i], "%s %s ", iter->key_.c_str(),
				   	iter->val_.c_str());
		}
		fclose(out[i]);
	}

	return 0;
}				/* ----------  end of function main  ---------- */
