/*
 * =====================================================================================
 *
 *       Filename:  pow.cpp
 *
 *    Description:  x pow n
 *
 *        Version:  1.0
 *        Created:  2012年08月22日 10时28分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

// p(x, n) = p(x, 1) * a0 * p(x,2) * a1  * p(x,4) * a2 * p(x, 8) * a3 * p(x, 16) * a4;

#include <stdio.h>
double pow(double x, int n) 
{
	double ret = 1.0;
	double x_p = x;
	while( n != 0 )
	{
		if( (n & 1) == 1 )
		{
			ret *= x_p;
		}
		x_p *= x_p;
		n >>= 1;
	}
	return ret;
}

template <typename T>
T pow_auxilary(T x, int n)
{
	T ret = static_cast<T>( 1 );
	T x_p = x;
	while( n != 0 )
	{
		if( (n & 1) == 1 )
		{
			ret *= x_p; 
		}
		x_p *= x_p;
		n >>= 1;
	}
	return ret;
}


int main(int argc, char *argv[])
{
	printf("%f \n", pow(2.3, 2));
	printf("%f \n", pow(2, 7));
	printf("%f \n", pow(2, 3));
	printf("%f \n", pow(2, 0));
	printf("%f \n", pow_auxilary(2.3, 2));
	printf("%d \n", pow_auxilary(2, 7));
	printf("%d \n", pow_auxilary(2, 3));
	printf("%d \n", pow_auxilary(2, 0));
	return 0;
}
