/*
 * =====================================================================================
 *
 *       Filename:  swap.cpp
 *
 *    Description:  to swap two object content
 *
 *        Version:  1.0
 *        Created:  2012年05月03日 10时22分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yuan DaXing (http://hi.baidu.com/%E8%A2%81%E5%A4%A7%E6%98%9F/home), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
#include <string>

namespace Implementation{
	class Example{
		private:
			std::string *p;
		public:
			Example(const std::string &str): p(new std::string(str)) { }
			void swap(Example &rhs) {
				std::cout << "call internal Example swap\n";
				std::swap(p, rhs.p);
			}
	};
	void swap(Example &lhs, Example &rhs) {
		lhs.swap(rhs);
	}

}

int main()
{
	using std::swap;
	Implementation::Example e("my Good"), e2("your God");
	swap(e, e2);

	return 0;
}

