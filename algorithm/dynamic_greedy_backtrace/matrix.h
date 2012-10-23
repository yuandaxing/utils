/*
 * =====================================================================================
 *
 *       Filename:  matrix.h
 *
 *    Description:  a implementation for matrix
 *
 *        Version:  1.0
 *        Created:  2012年07月01日 15时10分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef  MATRIX_H_INC
#define  MATRIX_H_INC
#include <vector>
namespace utils {
/* 
 * allow copy for the Matrix, and we just allowed primitive type
 */
template <typename T>
class Matrix {
	public:
		typedef std::vector<T> vec;

		Matrix(int row, int column) :
			row_(row), column_(column) {
			matrix_.assign(row, vec());		
			int i = 0;
			for ( i = 0; i < row; i += 1 ) {
				matrix_[i].assign(column_, static_cast<T>(0));
			}
		}
		~Matrix() { }
		const vec & operator[](int row) const {
			return matrix_[row];
		}
		vec & operator[](int row) {
			return matrix_[row];
		}
		int getRow() const {
			return row_;
		}
		int getColumn() const {
			return column_;
		}
	private:
		std::vector<vec> matrix_;
		const int row_, column_;
};
}

#endif   /* ----- #ifndef MATRIX_H_INC  ----- */
