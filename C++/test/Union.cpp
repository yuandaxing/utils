/*
 * =====================================================================================
 *
 *       Filename:  Union.cpp
 *
 *    Description:  G
 *
 *        Version:  1.0
 *        Created:  2012年09月20日 12时33分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include<stdio.h>
int main(){
	union V {
		struct X {
			unsigned char s1:2;
			unsigned char s2:3;
			unsigned char s3:3;
		} x;

		unsigned char c;
	} v;

	v.c = 100;
	printf("%d",sizeof(v));
	return 0;
}
