/*
 * =====================================================================================
 *
 *       Filename:  add.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012Äê04ÔÂ05ÈÕ 09ʱ30·Ö31Ãë
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

int add(int a, int b, int carry)
{
	if(a == 0 && b == 0)
		return carry;

	int result = (a ^ b ^ carry) & 1;
	carry = a & b & 1 || a & carry & 1 || b & carry & 1;
	
	return result ^  (add(a >> 1, b >> 1, carry) << 1);
}

int add2(int a,int b) {
	if(b == 0)
		return a;

	int c = a ^ b;
	int carry = (a & b) << 1;
	return add2(c,carry);
}
int main()
{
	printf("%d\t", add(7, 7, 0));
	printf("%d\t", add2(7, 7));
	printf("%d\t", add2(7, 15));
	printf("%d\t", add2(7, 15));
	return 0;
}
