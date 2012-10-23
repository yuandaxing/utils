/*
 * =====================================================================================
 *
 *       Filename:  Dynamic_Cast.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月08日 22时10分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
class Base {
	private:
		int i_;
	public:
		Base(int i = 10) : i_(i) { }
		void print(std::ostream &os) const {
			os << i_;
		}
		virtual ~Base() { }
};

std::ostream & operator<<(std::ostream &os, const Base & b) {
	b.print(os);
	return os;
}

class Derived : public Base {
	private:
		int j_;
	public:
		Derived(int j = 5, int i = 10) : Base(i), j_(j) { }
		void print(std::ostream & os) const {
			Base::print(os);
			os << j_;
		}
};
class A
{
	public:
	virtual ~A(){}
};
class B
{
	public:
	virtual ~B(){}
};
class C:public A,public B
{};
int main(int argc, char *argv[])
{
	Base *pb = new Derived(20, 30);
	A *pa=new C;
	B *pb2=dynamic_cast<B*>(pa);
	std::cout << (pb2) << std::endl;
	Derived *pd = dynamic_cast<Derived *>(pb);

	return 0;
}
