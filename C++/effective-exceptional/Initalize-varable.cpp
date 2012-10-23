/*
 * =====================================================================================
 *
 *       Filename:  Initalize-varable.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年09月29日 19时16分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <tr1/memory>
class SomeType {
	private:
		int d_;
	public:
		SomeType(int d = 0) : d_(d) { }
		~SomeType() { 
			std::cout << "decotr SomeType" << d_ << std::endl;
		}
};

int main(int argc, char *argv[])
{
	SomeType u(10);
	SomeType t1 = u;
	SomeType t2(u);
	SomeType t3(); //this is a function declaration
	SomeType t;
	std::tr1::shared_ptr<SomeType> sptr(new SomeType()); // right
	std::tr1::shared_ptr<SomeType> sptr1(new SomeType); //right too compare above
}
