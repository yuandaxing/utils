/*
 * =====================================================================================
 *
 *       Filename:  accumulate.cpp
 *
 *    Description:  test
 *
 *        Version:  1.0
 *        Created:  2012年08月24日 08时36分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <string>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <list>
int main() 
{
	std::string strs[] = {"abc", "def", "hig"};
	int is[] = {1, 2, 3};

	int sum = std::accumulate(is, is + 3, 0);

	std::cout << sum << std::endl;

	std::string s = std::accumulate(strs, strs + 3, std::string(""));

	std::cout << s << std::endl;

	std::vector<int> vi(2, 2);

	for(std::vector<int>::iterator iter = vi.begin(); iter != vi.end();
			iter++) {
		std::cout << *iter << std::endl;
	}

	std::cout << "testing backinserter\n";
	std::fill(vi.begin(), vi.end(), 0);
	std::fill_n(std::back_inserter(vi), 10, 3);

	for(std::vector<int>::iterator iter = vi.begin(); iter != vi.end();
			iter++) {
		std::cout << *iter << std::endl;
	}

	std::cout << "end testing backinserter\n";
	std::list<int> li(is, is + 3);
	std::list<int> li1(is + 1, is + 3);
	std::list<int>::iterator iter = li.begin();
	while((iter = std::find_first_of(iter, li.end(),
					li1.begin(), li1.end())) != li.end()) {
		std::cout << *iter << std::endl;
		iter++;
	}



	return 0;
}
