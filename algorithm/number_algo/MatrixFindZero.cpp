/*
 * =====================================================================================
 *
 *       Filename:  MatrixFindZero.cpp
 *
 *    Description:  find the column with most zeros
 *
 *        Version:  1.0
 *        Created:  2012年08月25日 14时45分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include <fstream>
#include <iostream>
#include "matrix.h"

int main(int argc, char *argv[])
{
	std::ifstream fin("matrix.txt");

	int column, row;

	fin >> row >> column;
	utils::Matrix<int> m(row, column);

	for( int i = 0 ; i < row ; i++ )
	{
		for( int j = 0 ; j < column ; j++ )
		{
			fin >> m[i][j];
		}
	}

	int maxrow = 0, maxzeros = 0;
	for( int i = 0, j = column - 1 ; i < row && j >= 0 ; )
	{
		if( m[i][j] == 0 )
		{
			j--;
			maxrow = i;
			maxzeros = column - j - 1;
		} else {
			i++;
		}
	}

	std::cout << "max_row :" << maxrow
		<< " 	max_zeros: " << maxzeros << std::endl;

	return 0;
	
}
