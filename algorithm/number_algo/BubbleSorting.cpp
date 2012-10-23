/*
 * =====================================================================================
 *
 *       Filename:  BubbleSorting.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月15日 11时17分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include <iostream>
#include <vector>
#include "../../Common.h"
template <typename T>
void BubbleSort( T *a, int size ) {
	for( int i = 0 ; i <  size - 1; i++ )
	{
		for( int j = 0 ; j < size - 1 - i ; j++ )
		{
			using std::swap;
			if( a[j] > a[j+1] ) swap( a[j], a[j+1] );
		}
		
	}
}

int main(int argc, char *argv[])
{
	int a[] = { 1, 3, 2, 7, 10, 0, 1 };
	const int len = sizeof(a) / sizeof(a[0]);
	std::vector<int> vi( a, a+len );

	BubbleSort(&vi[0], len);

	std::cout << vi;


}
