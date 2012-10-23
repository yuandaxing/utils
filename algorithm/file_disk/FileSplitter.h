/*
 * =====================================================================================
 *
 *       Filename:  Split.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月05日 21时12分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <iostream>
class FileSplitter {
	public:
		FileSplitter(const char *ifile, const char *ofile, uint64_t offset, 
				uint64_t size, const char *delimiter = " \t\n" ) : 
			fin_(fopen(ifile, "rb")), fout_(fopen(ofile, "wb")), 
			state_(false), delimiter_(delimiter), expectSize_(size), size_(0) {
			state_ = (fin_ != NULL && fout_ != NULL) ;
			if( state_ )
			{
				state_ = (fseeko(fin_, offset, SEEK_SET) == 0);
				if(!state_)
					std::cout << "cannot seek to pos: " << offset << std::endl;
			} else {
				std::cout << "cannot open or create file " << std::endl;
			}
		}
		uint64_t doSplit() {
			uint64_t n = expectSize_ / BuffSize + 1;
			for( uint64_t i = 0 ; i < n ; i++ )
			{
				int nSize = fread(buf_, 1, BuffSize, fin_);
				if(nSize > 0) {
					fwrite(buf_, 1, nSize, fout_);
					size_ += nSize;
				}
			}
			int ns;
			for( ns = 0 ; ns < BuffSize ; ns++ )
			{
				int nSize = fread(buf_ + ns, 1, 1, fin_);
				if( nSize != 1 || delimiter_.find(buf_[ns]) != std::string::npos )
				{
					break;
				}
			}
			if( ns > 0 )
			{
				size_ += ns;
				fwrite(buf_, 1, ns, fout_);
			}
			return size_;
		}

		~FileSplitter() {
			if(fin_)
				fclose(fin_);
			if(fout_)
				fclose(fout_);
		}

		bool state() {
			return state_;
		}
	private:
		FILE *fin_, *fout_;
		bool state_;
		enum { BuffSize = 4096};
		//enum { BuffSize = 10};
		char buf_[BuffSize];
		std::string delimiter_;
		uint64_t expectSize_;
		uint64_t size_;
};

bool Splite(const char *srcFile, uint64_t expectSize, const char *destFilePrefix, 
		const char *destFileSuffix, std::vector<std::string> &splits);
