/*
 * =====================================================================================
 *
 *       Filename:  CirclePermutation.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月07日 23时29分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <vector>
#include <iostream>
#include "../../Common.h"
template <typename T>
class CirclePermutation {
	public:
		template <typename Iter>
		CirclePermutation(const Iter &beg, const Iter &end) : 
			data_(beg, end) { }
		void printPM() {
			printPerHelper(1);
		}
	private:
		void printPerHelper(int i) {
			if( static_cast<unsigned>(i) >= data_.size()) {
				std::cout << data_ << std::endl;
				return ;
			}

			for( int j = i ; static_cast<unsigned>(j) < data_.size() ; j++ )
			{
				using std::swap;
				swap(data_[i],data_[j]);
				printPerHelper(i+1);
				swap(data_[i], data_[j]);
			}
		}
		std::vector<T> data_;
};


int main(int argc, char *argv[])
{
	int a[] = {1, 2, 3, 4};
	const int len = sizeof(a) / sizeof(a[0]);
	CirclePermutation<int>   cp(&a[0], a+len);
	cp.printPM();
	return 0;
}
