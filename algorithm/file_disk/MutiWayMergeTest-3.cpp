/*
 * =====================================================================================
 *
 *       Filename:  MutiWayMergeTest-3.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月05日 15时37分40秒
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
	MergeTask<Item, Compare1> mt("string-sorting.txt", 
			fileList, fileList+NFile);
	mt.doMerge();
	return 0;
}
