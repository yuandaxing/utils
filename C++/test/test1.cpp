/*
 * =====================================================================================
 *
 *       Filename:  test1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年07月10日 21时13分31秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int (*a1)[10];
	int b[9][10];
	a1 = b;
	if( argc < 2 )
	{
		printf("argument error\n");
		abort();
	}
	int a = atoi(argv[1]);
	printf("%d", a);
	printf("hello, world\n");
	assert(1 == 1);
	while( true )
	{
		break;
	}
	exit(0);
}
