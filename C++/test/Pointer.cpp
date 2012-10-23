/*
 * =====================================================================================
 *
 *       Filename:  Pointer.cpp
 *
 *    Description:  test base class pointer and derived class Pointer
 *
 *        Version:  1.0
 *        Created:  2012年09月19日 20时43分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdio.h>
class Base {
	private:
		int i_, j_, s_;
	public:
		Base(int i = 0, int j = 0, int s = 0) :
			i_(i), j_(j), s_(s) { }
	/* 	virtual */void print() {
			std::cout << "i_:" << i_ << " j_:" << j_
				<< " s_:" << s_ << std::endl;
		}
};

class Base1{
	private:
		int unused;
	public:
		Base1() : unused(10) { }
		/* virtual*/ void print1() {
			std::cout << unused << std::endl;
		}
};

class Derived : public Base1, public Base{
	private:
		int k_;
	public:
		Derived(int i = 0, int j = 0, int s = 0, int k = 0) :
			Base(i, j, s), k_(k) { }

		void print() {
			Base::print();
			std::cout << "k_:" << k_ << std::endl;
		}	
};

int main(int argc, char *argv[])
{
	Base *b = NULL;
	Derived *d = NULL;
	Base1 *b1 = NULL;
	Derived der;
	b = &der;
	d = &der;
	b1 = &der;
	printf("%d, %d, %d\n", sizeof(Base), sizeof(Base1), sizeof(Derived));
	printf("%x, %x, %x\n", b, d, b1);
	return 0;
}
