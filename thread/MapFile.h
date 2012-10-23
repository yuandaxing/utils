/*
 * =====================================================================================
 *
 *       Filename:  MapFile.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年05月25日 18时23分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
/*-----------------------------------------------------------------------------
 *  the mapfile support binary and string data storage, and the disk data formate
 *  is      length+data
 *-----------------------------------------------------------------------------*/
#ifndef  _MAPFILE_H_INC
#define  _MAPFILE_H_INC
#include < boost/scoped_ptr.hpp >
#include < stdio.h >
namespace threadSafe {
class MapFile {
	private:
		bool rw ;
		uint16_t index_iterval;
		string dataFile ;
		string indexFile ;
		/*-----------------------------------------------------------------------------
		 *  raw file type for effeciency
		 *-----------------------------------------------------------------------------*/
		FILE  *dfp, *ifp ; 
		using boost::scoped_ptr ; // to set our buff
		scoped_ptr< char * > dbuff;
		

		static inline void appendBlock ( FILE *f, 
				const void *data, const int len ) {

		}

		static inline FILE * openFile ( const char * fileName, 
				const char *mode ) {
			FILE *f = fopen ( fileName, mode ) ;
			if ( f == NULL ) {
				ERR << "cannot open file:" << fileName << std::endl ;
				throw exception ( "FILE OPEN\n" ) ;
			}
		}

		MapFile ( bool rw_, const string & fileName, 
				const uint32_t iterval, const uint32_t bufSize = BUFSIZ ) ; 
		~ MapFile ( ) ;

		// for write
		void append ( const void *key, const uint32_t klen, const void *val, 
				const uint32_t  vlen ) ;
		void finishAppend ( ) ;
		
		// for read
		
};

MapFile::MapFile ( bool rw_, const string & fileName, 
		const uint32_t iterval = 128, const uint32_t bufSize = BUFSIZ ) 
		: rw ( rw_ ), index_iterval ( iterval ), dfp ( NULL ) , 
		ifp ( NULL) , dbuff ( new char [bufSize] ) {	

			time_t cur = time ( 0 ) ;
			ostringstream oss ;
			oss << fileName << cur ;

			dataFile = oss.str ( ) ;
			dataFile.append ( ".dat" ) ;
			indexFile = oss.str ( ) ;
			indexFile.append ( ".ind" ) ;

			ifp = fopen ( indexFile.c_str(), "wb" ) ;
			if ( dfp == NULL ) {
				ERR << "cannot open data file:" << indexFile << std::endl ;
				throw exception ( "FILE OPEN\n" ) ;
			}

			setbuf ( dataFile, dbuf.get() ) ;
}

}

#endif   /* ----- #ifndef _MAPFILE_H_INC  ----- */

