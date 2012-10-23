/*
 * =====================================================================================
 *
 *       Filename:  FileSplitter.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月05日 23时41分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <assert.h>
#include <errno.h>
#include "FileSplitter.h"
#include <sys/stat.h>
#include <iostream>
#include <sstream>
const uint64_t Splice = 1024 * 1024 * 256;
//const uint64_t Splice = 20;
bool Splite(const char *srcFile, uint64_t expectSize, const char *destFilePrefix, 
		const char *destFileSuffix, std::vector<std::string> &splits) {
	struct stat attr;
	if( stat(srcFile, &attr) < 0 )
	{
		std::cout << "can not get state\n";
	}

	uint64_t total = attr.st_size;
	int nSlice = total / expectSize + 2;

	uint64_t start = 0;
	for( int i = 0 ; i < nSlice ; i++ )
	{
		if(start >= total)
			return true;

		std::string temp(destFilePrefix);
		std::ostringstream oss1;
		oss1 << '-' << i << '.' << destFileSuffix;
		temp += oss1.str();

		FileSplitter fsp(srcFile, temp.c_str(), start, expectSize);
		if(!fsp.state()) {
			std::cout << "file state error " << std::endl;
			break;
		}
		uint64_t nCurSize = fsp.doSplit();
		if( nCurSize > 0 )
		{
			splits.push_back(temp);
			start += nCurSize;
		} else {
			break;
		}
	}

	return false;
}

int main(int argc, char *argv[])
{
	std::vector<std::string> splits;
	assert(Splite("test.txt", Splice, 
				"split", "txt", splits) == true);

	return 0;
}
