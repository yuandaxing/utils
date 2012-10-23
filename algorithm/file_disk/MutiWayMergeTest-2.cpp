/*
 * =====================================================================================
 *
 *       Filename:  MutiWayMerge.cpp
 *
 *
 *        Version:  1.0
 *        Created:  2012年09月28日 16时54分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "MergeFileList.h"
#include "MutiWayMerge.h"

int main(int argc, char *argv[])
{
	MergeTask<int, std::greater<int> > mt("test-sorted.txt", fileList, fileList + NFile);
	mt.doMerge();
	return 0;
}

