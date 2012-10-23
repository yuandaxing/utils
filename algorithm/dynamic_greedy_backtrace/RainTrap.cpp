/*
 * =====================================================================================
 *
 *       Filename:  RainTrap.cpp
 *
 *    Description:  Given a non-negative integer array representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining. For example, given [0,1,0,2,1,0,1,3,2,1,2,1], returns 6.
 *    we just need to comput the max[0---i] array, and max[n-1 ----- i] array
 *
 *        Version:  1.0
 *        Created:  2012年08月19日 12时07分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include <algorithm>
#include <iostream>

void max_forward(int a[], int len, int max[]) {
	if( len < 1 )
	{
		return ;
	}

	int i;
	max[0] = a[0];
	for( i = 1 ; i < len ; i++ )
	{
		if( a[i] > max[i-1] )
		{
			max[i] = a[i];
		} else {
			max[i] = max[i-1];
		}
	}
}

void max_backward(int a[], int len, int max[]) {
	if(len < 1)
		return ;

	max[len - 1] = a[len - 1];
	for( int i = len - 2 ; i >= 0 ; i-- )
	{
		if( a[i] > max[i+1] )
		{
			max[i] = a[i];
		} else {
			max[i] = max[i+1];
		}
	}
}
int main(int argc, char *argv[])
{
	int a[100], b[100];
	int c[] = {
		0,1,0,2,1,0,1,3,2,1,2,1
	};
	
	
	const int len = sizeof(c) / sizeof(int);

	max_backward(c, len, a);
	max_forward(c, len, b);

	int sum = 0;

	for( int i = 1 ; i < len -1 ; i++ )
	{
		int min = std::min(b[i-1], a[i+1]);
		if(c[i] < min) {
			sum += min - c[i];
		}		
	}
	
	std::cout << sum << std::endl;
	return 0;
}
