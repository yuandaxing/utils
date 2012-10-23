/*
 * =====================================================================================
 *
 *       Filename:  MagicalNumber.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月14日 00时24分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "../../Common.h"
#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
class MagicalNumber {
	public:
		MagicalNumber() : vi_(5, 0), 
			bs_(0), cur_(0), magical(0) { }

		bool gen();
		void print() {
			std::cout << vi_;
			int cur_sum = 0;
			std::vector<int> inte;

			for( int i = 0 ; i < 32 ; i++ )
			{
				cur_sum = cur_sum / 2 + vi_[(i+4) % 32] * 16;
				std::cout << cur_sum << " ";
				inte.push_back(cur_sum);
			}
			std::cout << std::endl;
			std::sort(inte.begin(), inte.end());
			std::cout << inte;
		}

	private:
		std::vector<int> vi_;
		std::bitset<32> bs_;
		int cur_;
		int magical;
};

bool MagicalNumber::gen() {
	if( vi_.size() == 32 )
	{
		for( int i = 0 ; i < 5 ; i++ )
		{
			if( bs_[cur_] == true ) 
				return false;
			cur_ /= 2;
		}
		return true;
	} else {
		int s_cur = cur_;

		if( bs_[s_cur] == true )
			return false;

		bs_[s_cur] = true;
		vi_.push_back(0);
		cur_ = s_cur / 2;
		if( gen() ) return true;
		vi_.pop_back();

		vi_.push_back(1);
		cur_ = s_cur / 2 + 16;
		if( gen() ) return true;
		vi_.pop_back();

		bs_[s_cur] = false;
		return false;
	}
}


int main(int argc, char *argv[])
{
	MagicalNumber mg;
	mg.gen();
	mg.print();
	return 0;
}
