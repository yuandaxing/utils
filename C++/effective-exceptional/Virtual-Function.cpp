/*
 * =====================================================================================
 *
 *       Filename:  Virtual-Function.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年09月30日 18时58分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <complex>
using namespace std;

class Base {
	public:
		virtual void f( int ) {
			cout << "Base::f(int)" << endl;
		}

		virtual void f( double ) {
			cout << "Base::f(double)" << endl;
		}

		virtual void g( int i = 10 ) {
			cout << i << endl;
		}
};

class Derived: public Base {
	public:
		//Derived does not overload Base::f... it hides them. This distinction is very important, because it means 
		//that Base::f(int) and Base::f(double) are not visible in Derived! 
		//(Note that certain popular compilers do not even emit a warning for this.)
		//    [RULE] When providing a function with the same name as an inherited function, be sure to bring the inherited functions into scope with a "using" declaration if you don't want to hide them.
		void f( complex<double> ) { //i think it is just annother function
			cout << "Derived::f(complex)" << endl;
		}

		void g( int i = 20 ) {
			cout << "Derived::g() " << i << endl;
		}
};

int main() {
	Base    b;
	Derived d;
	Base*   pb = new Derived;

	b.f(1.0); //Base::f(double)
	d.f(1.0);//it hide the base class f function
	pb->f(1.0);//Base::f(double)

	b.g(); //10
	d.g();//Derived::g() 20
	pb->g(); //derived::g() 10

	delete pb; //you should make base dector virtual
}
