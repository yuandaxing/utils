/*
 * =====================================================================================
 *
 *       Filename:  testFileUtils.cc
 *
 *    Description:  :
 *
 *        Version:  1.0
 *        Created:  2012年05月27日 10时28分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <FileUtils.h>
#include <string>
#include <vector>
#include <iostream>
#include <assert.h>
using namespace threadSafe ;
using namespace std ;

int main ( ) {
	const string remove = "./test.txt" ;
	const string dir = "/home/ydx" ;

	vector<string> files ;

	remove_file(remove);

	assert( get_children_files(dir, 
				files) == 0 ) ;

	for ( vector<string>::iterator iter=
			files.begin(); 
			iter != files.end();
			++iter ) {
		cout << *iter << "\t" << std::endl ;
	}


	return 0 ;

}
