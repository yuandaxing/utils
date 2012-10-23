/*
 * =====================================================================================
 *
 *       Filename:  WaterHolder.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月15日 22时57分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <climits>
#include <iostream>
#include <algorithm>

int holderWater( int *a, int len ) {
	int sum = 0;
	int start = 0, end = len - 1;
	int maxPre = a[0], maxLast = a[end];

	while( start <= end )
	{
		int min, mm = std::min( maxLast, maxPre );

		if( a[start] < a[end] )
		{
			min = a[start];
			start++;
			maxPre = std::max( maxPre, a[start] );
		} else {
			min = a[end];
			end--;
			maxLast = std::max( maxLast, a[end] );
		}
		
		if( min < mm )
		{
			sum += (mm - min);
		}

	}
	return sum;
}


int main(int argc, char *argv[])
{
	int a[] = {3, 4, 1, 2, 5, 2, 7, 0};
	const int len = sizeof(a) / sizeof(a[0]);
	std::cout << holderWater( a, len ) << std::endl ; 

	return 0;
}
