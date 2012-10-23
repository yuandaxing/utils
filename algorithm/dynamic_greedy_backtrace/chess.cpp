/*
 * =====================================================================================
 *
 *       Filename:  chess.cpp
 *
 *    Description:  象棋的将和帅不能相遇在同一条直线上，写出一个程序，列举合法将帅的所有组合
 *
 *        Version:  1.0
 *        Created:  2012年08月16日 17时28分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
typedef struct{
	unsigned char a : 4;
	unsigned char b : 4;
} easy_chess;

void printf_conflict( )
{
	char i = 81;
	while( i-- )
	{
		if( i / 9 % 3 == i % 9 % 3 )
		{
			continue;
		}

		printf(" A : %d B : %d\n", i / 9 + 1, i % 9 + 1 );
	}
}

int main ( int argc, char *argv[] )
{
	easy_chess i;

	for( i.a = 1 ; i.a <= 9 ; i.a++ )
	{
		for( i.b = 1 ; i.b <= 9 ; i.b++ )
		{
			if( i.a % 3 != i.b % 3 )
			{
				printf("A : %d, B : %d\n", i.a, i.b);
			}
		}
	}
	
	printf("\n\n\n");
	printf_conflict();
	return 0;
}				/* ----------  end of function main  ---------- */
