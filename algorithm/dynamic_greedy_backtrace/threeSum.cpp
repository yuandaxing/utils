/*
 * =====================================================================================
 *
 *       Filename:  threeSum.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年07月04日 19时12分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>
#include <set>
struct Triple {
	Triple(int x, int y, int z) :
		x_(x), y_(y), z_(z) { }
	int x_, y_, z_;
};

std::ostream & operator<< ( std::ostream & out, const Triple &t) {
	out << "(" << t.x_ << "," << t.y_ << "," << t.z_ << ") ";
	return out;
}
bool operator< (const Triple &lhs, const Triple &rhs) {
	if(lhs.x_ != rhs.x_)
		return lhs.x_ - rhs.x_;

	if(lhs.y_ != rhs.y_)
		return lhs.y_ - rhs.y_;

	return lhs.x_ - rhs.z_;
}


typedef std::vector<std::pair<int, int> >  vpii;
vpii twoSum(const int sum, int *array, const int len) {
	int i = 0, j = len - 1;
	vpii v;
	while(i < j) {
		int cur = array[i] + array[j];
		if ( cur < sum) {
			i++;	
		} else if ( cur > sum ) {
			j--;
		} else {
			v.push_back(std::make_pair(array[i], array[j]));
			i++; j--;
		}
	}
	return v;
}

void searchAllThreeSum(std::set<Triple> &ret, std::vector<int> &nums, const int sum) {
	std::sort(nums.begin(), nums.end());

	int i = 0;
	for ( i = 0; static_cast<unsigned>(i) < nums.size() - 1; i += 1 ) {
		vpii v = twoSum(sum - nums[i], &nums[i + 1], nums.size() - i - 1);
		int j = 0;
		for ( j = 0; static_cast<unsigned>(j) < v.size(); j += 1 ) {
			ret.insert(Triple(nums[i], v[j].first, v[j].second));
		}
	}
}	



int main ( int argc, char *argv[] )
{
	int a[] = {-1, 0, 1, 2, -1, -4};
	const int len = sizeof(a) / sizeof(int);
	int i = 0;
	std::vector<int> vi;
	for ( i = 0; i < len; i += 1 ) {
		vi.push_back(a[i]);
	}
	std::set<Triple> vt;
	searchAllThreeSum(vt, vi, 0);

	for ( std::set<Triple>::iterator iter = vt.begin() ;
			iter != vt.end(); iter++ ) {
		std::cout << *iter;
	}
	std::cout << std::endl;
	return 0;
}				/* ----------  end of function main  ---------- */

