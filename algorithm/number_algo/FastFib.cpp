/*
 * =====================================================================================
 *
 *       Filename:  FastFib.cpp
 *
 *    Description:  fast fibinacci number generator
 *
 *        Version:  1.0
 *        Created:  2012年09月28日 14时48分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
const int a[2][2] = {{1,1},{1,0}};
const int n0[2][2] = {{1,0},{0,1}};

void comp2X2Matrix(int r[][2], const int s1[][2], const int s2[][2]) {
	int result[2][2];
	result[0][0] = s1[0][0] * s2[0][0] + s1[0][1] * s2[1][0];
	result[0][1] = s1[0][0] * s2[0][1] + s1[0][1] * s2[1][1];
	result[1][0] = s1[1][0] * s2[0][0] + s1[1][1] * s2[1][0];
	result[1][1] = s1[1][0] * s2[0][1] + s1[1][1] * s2[1][1];
	r[0][0] = result[0][0];
	r[0][1] = result[0][1];
	r[1][0] = result[1][0];
	r[1][1] = result[1][1];
}


void Fib(int result[][2], int n) {
	if(n == 0) {
		result[0][0] = n0[0][0];
		result[0][1] = n0[0][1];
		result[1][0] = n0[1][0];
		result[1][1] = n0[1][1];
	} else if((n & 1) == 1) {
		Fib(result, n-1);
		comp2X2Matrix(result, a, result);
	} else {
		Fib(result, n >> 1);
		comp2X2Matrix(result, result, result);
	}
}
int Fn(int r[][2]) {
	return r[0][0] + r[0][1];
}
int main(int argc, char *argv[])
{
	int a[2][2];
	Fib(a, 1);
	std::cout << Fn(a) << std::endl;


	Fib(a, 2);
	std::cout << Fn(a) << std::endl;


	Fib(a, 20);
	std::cout << Fn(a) << std::endl;
}
