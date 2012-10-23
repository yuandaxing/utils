/*
 * =====================================================================================
 *
 *       Filename:  MergeFileList.h
 *
 *    Description:  list the file for test
 *
 *        Version:  1.0
 *        Created:  2012年09月29日 09时33分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>


const char *fileList[] = {
	"test-1.txt",
	"test-2.txt",
	"test-3.txt",
	"test-4.txt",
	"test-5.txt",
	"test-6.txt",
	"test-7.txt",
	"test-8.txt",
	"test-9.txt",
	"test-10.txt",
	"test-11.txt",
	"test-12.txt",
	"test-13.txt",
	"test-14.txt",
	"test-15.txt",
	"test-16.txt",
	"test-17.txt",
	"test-18.txt",
	"test-19.txt",
	"test-20.txt",
	"test-21.txt",
};

const int NFile = sizeof(fileList) / sizeof(fileList[0]);

class Item {
	public:
		std::string key_;
		std::string val_;
	public:
		Item(const char *key="", const char *v="") :
			key_(key), val_(v) { }
		friend std::ostream & operator<<(std::ostream &os, const Item &item);
		friend std::istream & operator>>(std::istream &is, Item &item);
		friend class Compare;
};

class Compare {
	public:
		bool operator()(const Item &lhs, const Item &rhs) const {
			return lhs.key_ > rhs.key_;
		}
};

class Compare1 {
	public:
		bool operator()(const Item &lhs, const Item &rhs) const {
			return lhs.key_ <  rhs.key_;
		}
};

std::ostream & operator<<(std::ostream &os, const Item &item) {
	os << item.key_<< " " << item.val_ << " ";
	return os;
}
std::istream & operator>>(std::istream &is, Item &item) {
	is >> item.key_ >> item.val_;
	return is;
}
