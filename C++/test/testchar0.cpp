/*
 * =====================================================================================
 *
 *       Filename:  testchar0.cpp
 *
 *    Description:  test
 *
 *        Version:  1.0
 *        Created:  2012年09月16日 22时56分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdlib.h>
#include <string.h>
typedef struct item {
	int i, j;
	char a[0];
	void *b[];
} item;

int main(int argc, char *argv[])
{
	item it;
	item *p = (item *) malloc( 100 );
	memset(p->a, 0, 100 - sizeof(item));
	std::cout << sizeof(item) << std::endl;

	std::cout << it.a << " " << it.b << std::endl;
	
	strcpy(p->a, "aaaaaaaaaaaaaaaaaa");

	std::cout << p->a << std::endl;

	std::cout << (char *)p->b << std::endl;

	return 0;
}
