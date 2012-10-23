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
#include <string>
#include <list>
#include <stdlib.h>
class SomeType {
	private:
		int d_;
	public:
		SomeType(int d = 0) : d_(d) { }
		~SomeType() { 
			std::cout << "decotr SomeType" << d_ << std::endl;
		}
		bool operator==(const SomeType &st) {
			return d_ == st.d_;
		}
};

using namespace std;
string FindAddr( list<SomeType> l, string name ) //l and name should be ref, and should be const
{
	for( /*list<Employee>::iterator*/auto i = l.begin();
			i != l.end();
			i++ ) // prefer post incr
	{
		if( *i == atoi(name.data()) ) //every time a temp obj is created
		{       // make ctor explicit
			return string("fuck");
		}
	}
	return string("notFind"); 
}


int main(int argc, char *argv[])
{
}
