/*
 * =====================================================================================
 *
 *       Filename:  testOrder.cc
 *
 *    Description:  big endian or little endian
 *
 *        Version:  1.0
 *        Created:  2012年06月02日 20时35分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <endian.h>
#include <stdio.h>
int main (	) {
#if __BYTE_ORDER == __LITTLE_ENDIAN
	printf("__LITTLE_ENDIAN\n");
#elif __BYTE_ORDER == __BIG_ENDIAN
	printf("__BIG_ENDIAN\n");
#endif

	return 0;
}
