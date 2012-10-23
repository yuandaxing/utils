/*
 * =====================================================================================
 *
 *       Filename:  testMatrix.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年07月01日 15时49分07秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "matrix.h"
#include <stdio.h>
using namespace utils;
void print_m(Matrix<int> &m) {
	int i = 0, j = 0;	
	for ( i = 0; i < m.getRow(); i += 1 ) {
		for ( j = 0; j < m.getColumn(); j += 1 ) {
			printf("%3d  ", m[i][j]);
		}
		printf("\n");
	}
}
int main ( int argc, char *argv[] )
{
	const int row = 10, column = 10;
	Matrix<int> m_int(row, column);
	int i = 0, j = 0;
	for ( i = 0; i < row; i += 1 ) {
		for ( j = 0; j < column; j += 1 ) {
			m_int[i][j] = i * j;
		}
	}
	print_m(m_int);
	return 0;
}				/* ----------  end of function main  ---------- */
