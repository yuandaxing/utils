/*
 * =====================================================================================
 *
 *       Filename:  FileUtils.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年05月26日 21时18分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef  _FILEUTILS_H_INC
#define  _FILEUTILS_H_INC
#include <stdio.h>
#include <string>
#include <Logger.h>
#include <dirent.h>
#include <Logger.h>
#include <vector>
namespace threadSafe {

/*-----------------------------------------------------------------------------
 *  just swallow the err, if write failed, we can just delete the file
 *-----------------------------------------------------------------------------*/
using std::string ;
using std::vector ;
static inline void remove_file ( const string &file_name ) {
	int ret = remove ( file_name.c_str() ) ;
	if ( ret != 0 )
		ERR << "cannot remove file: " << file_name
			<< std::endl ;
}

static inline size_t write_unlock ( const void *ptr, 
		size_t size, FILE *fp ) {
	return fwrite ( ptr, 1, size, fp ) ;
}

static inline size_t read_unlock ( void *ptr, 
		size_t size, FILE *fp ) {
	return fread ( ptr, 1, size, fp ) ;
}

static inline int get_children_files ( const string &dir, 
		vector<string> &files ) {
	DIR *dp ;
	struct dirent *dirp ;

	string temp(dir);
	if ( temp[temp.size() - 1] != '/' )
		temp.append("/");

	if ( (dp = opendir(dir.c_str())) == NULL ) {
		ERR << "ERR open dir " << dir << std::endl ;
		return errno ;
	}

	while ( (dirp = readdir(dp)) != NULL ) {
		if( strcmp(dirp->d_name, ".") != 0 &&
				strcmp(dirp->d_name, "..") != 0 )
			files.push_back ( temp + dirp->d_name ) ;
	}

	closedir ( dp ) ;
	return 0 ;
}

}
#endif   /* ----- #ifndef _FILEUTILS_H_INC  ----- */
