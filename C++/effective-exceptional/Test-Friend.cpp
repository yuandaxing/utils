/*
 * =====================================================================================
 *
 *       Filename:  Test-Friend.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年09月29日 22时07分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>


class Out {
	private:
		class Inner {
			public:
				int i;
		};

		friend int geti(Inner &i) {
			return i.i;
		}

	public: 
		static Inner* getInner () {
			return new Inner;
		}
};



int main(int argc, char *argv[])
{
	return 0;
}
