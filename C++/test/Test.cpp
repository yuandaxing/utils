/*
 * =====================================================================================
 *
 *       Filename:  Test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月07日 13时59分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <iostream>
class Test {
	private:
		int i;
	public:
		Test(int i) : i(i) { std::cout << i << std::endl;  }
};
/* void f() {
	return 1;
}*/
struct a {
	int i;
	struct b{
		int s;
	}p;
};

struct a k = {1, {1}};
int main(int argc, char *argv[])
{
	void *p = NULL;
	printf("%p", p);

	Test t(10);
	return 0;
}
