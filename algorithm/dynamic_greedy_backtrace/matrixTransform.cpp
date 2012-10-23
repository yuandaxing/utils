/*
 * =====================================================================================
 *
 *       Filename:  matrixTransform.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年06月30日 21时47分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "matrix.h"
#include <iostream>
using namespace utils;

bool transformHelper(Matrix<int> &matrix, int row, int column, int x, int y, bool check) {
	if(row ==  matrix.getRow() - 1 && x != 0) return false;
	if(column == matrix.getColumn() - 1 && y != 0) return false;
	if(check && x != 0 && matrix[row + 1][column] < x) return false;
	if(check && y != 0 && matrix[row][column + 1] < y) return false;
	if ( x != 0 ) {
		matrix[row + 1][column] -= x;
	}
	if ( y != 0 ) {
		matrix[row][column + 1] -= y;
	}
	return true;
}
void zigzag(int row, int column, int &n_row, int &n_column, const Matrix<int> &m) {
	if(row == 0 || column == m.getColumn() - 1) {
		n_row = row + column + 1 ;
		n_column = 0;
		//fix 
		if(n_row >= m.getRow()) {
			n_column = n_row - (m.getRow() - 1);
			n_row = m.getRow() - 1;
		}
	}
	else {
		n_row = row - 1;
		n_column = column + 1;
	}
}

bool couldTransform(Matrix<int> &m, int row, int column) {
	if ( row == m.getRow() - 1 && column == m.getColumn() - 1 ) {
		if ( m[row][column] == 0 ) {
			return true;
		}
		return false;
	}

	int next_column, next_row;
	zigzag(row, column, next_row, next_column, m);
	if ( m[row][column] == 0 ) {
		return couldTransform(m, next_row, next_column);
	}

	int i = 0;
	bool result = false;
	
	for ( i = 0; i <= m[row][column]; i += 1 ) {
	//try all the possibilities	
		if ( transformHelper(m, row, column, i, m[row][column] - i, true) ) {
			result = couldTransform(m, next_row, next_column);
			//go back into init state
			transformHelper(m, row, column, -i, i - m[row][column], false);
			if(result) return result;
		}
	}
	return false;
}

					
int main ( int argc, char *argv[] )
{
	const int row = 4, column = 4;
	int matrix[row][column] = {
		{2, 2}, 
		{2, 2}
	};

	int matrix_a[row][column] = {
		{0, 0, 2, 3},
		{0, 0, 1, 2},
		{2, 1, 0, 0},
		{3, 2, 0, 0}
	};
	int matrix_b[row][column] = {
		{0, 0, 2, 4},
		{0, 1, 2, 2},
		{2, 2, 1, 0},
		{4, 2, 0, 0}
	};
	Matrix<int> m(row, column);
	int i = 0, j = 0;
	for ( i = 0; i < row; i += 1 ) {
		for ( j = 0; j < column; j += 1 ) {
			m[i][j] = matrix_a[i][j];
		}
	}
	std::cout << couldTransform(m, 0, 0) << std::endl;
	return 0;
}				/* ----------  end of function main  ---------- */
