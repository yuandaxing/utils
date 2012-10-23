/*
 * =====================================================================================
 *
 *       Filename:  testStableSorting.cpp
 *
 *    Description:  test stable sorting and some functor
 *
 *        Version:  1.0
 *        Created:  2012年09月16日 18时02分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
std::ostream & operator<<(std::ostream &os, std::vector<int> &vci) {
	for( int i = 0 ; static_cast<unsigned>(i) < vci.size() ; i++ )
	{
		os << vci[i] << " ";
	}
	return os;	
}
int main(int argc, char *argv[])
{
	int a[] = { 1, 3, 5, 7, 7, 5, 3, 2, 1, 0, 9, 7, 8};
	const int len = sizeof(a) / sizeof(a[0]);
	std::vector<int> vi(a, a+len);

	std::stable_sort(vi.begin(), vi.end());

	std::cout << vi << std::endl;

	std::stable_sort(vi.begin(), vi.end(), std::less<int>());

	std::cout << vi << std::endl;

	//not stable now
	std::stable_sort(vi.begin(), vi.end(), std::greater_equal<int>());
	std::cout << vi << std::endl;

	std::stable_sort(vi.begin(), vi.end(), std::greater<int>());
	std::cout << vi << std::endl;

	return 0;
}
