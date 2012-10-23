/*
 * =====================================================================================
 *
 *       Filename:  boost_function.cpp
 *
 *    Description:  to show how to use function
 *
 *        Version:  1.0
 *        Created:  2012年08月25日 19时03分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>

#include <vector>

#include <boost/function.hpp>

#include <boost/bind.hpp>
#include <string>
using namespace std;

void print(int a, int b)

{

	cout << a << "," << b << endl;

}

class Test_Print{
	public:
		Test_Print(const std::string &h) :
			hold(h) { }
		void print(int k , const std::string &arg ) {
			std::cout << "K : " << k  << hold
				<< arg << std::endl;
		}
	private:
		std::string hold;
};

typedef boost::function<void (int)> SuccessPrint;

int main(int argc, char **argv)

{

	vector<SuccessPrint> printList;

	SuccessPrint printOne = boost::bind(print, _1, 2);

	printList.push_back(printOne);

	SuccessPrint printTwo = boost::bind(print, _1, 2);

	printList.push_back(printTwo);

	SuccessPrint printThree = boost::bind(print, _1, 2);

	printList.push_back(printThree);

	Test_Print tp("help me");

	//here we must use &, or it cannot compile, the arg sequence is the same as print func
	SuccessPrint print_class = boost::bind(&Test_Print::print, tp, _1, "Daxing");

	printList.push_back(print_class);
	
	for (int i = 0; static_cast<unsigned>(i) < printList.size(); ++i)

	{

		printList.at(i)(i);

	}
	return 0;
}
