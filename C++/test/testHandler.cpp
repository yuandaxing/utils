/*
 * =====================================================================================
 *
 *       Filename:  testHandler.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年09月16日 14时24分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "Handler.h"
#include <iostream>
class Test {
	public:
		Test(int i = 0, int j = 0) :
			i_(i), j_(j) {
				std::cout << "construct Test(i,j)\n";
			}
		Test(const Test& t):
			i_(t.i_), j_(t.j_) {
				std::cout << "construct Test(const Test&)\n";
			}
		Test & operator=(const Test& t) {
			i_ = t.i_;
			j_ = t.j_;
			return *this;
		}
		~Test() {
			std::cout << "destruct test\n";
		}
		void print() {
			std::cout << "i_:" << i_ << " j_:" << j_ << std::endl;
		}
	friend std::ostream & operator<<(std::ostream& os, 
			const Test &t);
	private:
		int i_, j_;
};

std::ostream & operator<<(std::ostream& os, const Test &t){
	os << "test:" << t.i_ << " " << t.j_ << std::endl;
	return os;
}

Handler<Test> getHandler(Test *t) {
	return t;
}
int main(int argc, char *argv[])
{
	Test *t = new Test();
	Test *t2 = new Test(10, 20);

	Handler<Test> h1(t), h2(h1);
	h2 = h1;
	h1 = h1;
	h2 = h2;
	Handler<Test> h3 = getHandler(t2);

	std::cout << *(h3.getRaw());
	h3->print();
	return 0;
}
