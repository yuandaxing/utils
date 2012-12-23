/*
 * =====================================================================================
 *
 *       Filename:  Iter.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年12月18日 23时27分16秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <list>
template <typename InputIterator, typename OutputIterator, typename Container>
void testIter(InputIterator b, InputIterator e, OutputIterator o, Container &c) {
	std::cout << "before copy:";
	for(auto iter = c.begin(); iter != c.end() ; ++iter )
	{
		std::cout << *iter << ",";
	}
	std::cout << std::endl;

	std::copy(b, e, o);

	std::cout << "after copy:";
	for(auto iter = c.begin(); iter != c.end() ; ++iter )
	{
		std::cout << *iter << ",";
	}
	std::cout << std::endl;
	
}
int main(int argc, char *argv[])
{
	//test inserter
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
	std::vector<int> vi1, vi2, vi3;
	std::list<int> li1, li2, li3;

	//test back_inserter
	std::copy(a, a + sizeof(a) / sizeof(int) , std::back_inserter(vi1));
	testIter(vi1.begin(), vi1.end(), std::back_inserter(vi2), vi2);

	//test front_inserter
	testIter(vi1.begin(), vi1.end(), std::front_inserter(li1), li1);

	//test istream_iterator ostream_iterator
//	std::istream_iterator<int> icin(std::cin);
//	std::istream_iterator<int> end;
//	testIter(icin, end, std::inserter(vi3, vi3.begin()), vi3);
//	//we need to clear the state
//	std::cin.clear();
//
	//test iterator operator
	std::vector<int>::iterator iter = vi1.begin();
	std::advance(iter, 3);
	std::cout << *iter << std::endl;

	std::copy(vi1.begin(), vi1.end(), std::ostream_iterator<int>(std::cout, ","));
	std::cout << std::endl;


	//test fill
	vi3.resize(20, 0);
	std::fill( vi3.begin(), vi3.end(), 10 );
	std::copy( vi3.begin(), vi3.end(), std::ostream_iterator<int>(std::cout, ",") );

	std::cout << std::endl;
	//test fill_n
	std::fill_n( vi3.begin(), 5, 20 );
	std::copy( vi3.begin(), vi3.end(), std::ostream_iterator<int>(std::cout, ",") );
	std::cout << std::endl;


	//test for replace
	std::replace( vi3.begin(), vi3.end(), 10, 15 );
	std::copy( vi3.begin(), vi3.end(), std::ostream_iterator<int>(std::cout, ",") );
	std::cout << std::endl;


	std::reverse_copy( vi1.begin(), vi1.end(), vi3.begin() );
	std::copy( vi3.begin(), vi3.end(), std::ostream_iterator<int>(std::cout, ",") );
	std::cout << std::endl;

	return 0;
}
