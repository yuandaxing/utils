/*
 * =====================================================================================
 *
 *       Filename:  ComplicateDerived.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年09月29日 21时51分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
class ExBase{
	private:
		static int d_;
	public:
		static void print() { std::cout << d_; }
		static int * get() {
			return &d_;
		}
};
int ExBase::d_ = 10;

class Der1 : public ExBase {

};
class Der2 : public ExBase {

};

class ExDer : public Der1, public Der2 {

};
int main(int argc, char *argv[])
{
	ExDer e;
	e.print();
	std::cout << std::endl;
	e.Der1::print();
	std::cout << std::endl;

	std::cout << (e.Der1::get() == e.Der2::get()) 
		<< std::endl;
	return 0;
}
