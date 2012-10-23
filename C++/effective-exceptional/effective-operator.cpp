/*
 * =====================================================================================
 *
 *       Filename:  effective-operator.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年09月30日 10时45分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>

template <typename T>
class Complex {
	private:
		T real_, imaginary_;
	public:
		Complex(T r, T i = 0) :
			real_(r), imaginary_(i) { }
		
		const Complex & operator+=(const Complex &c) {
			real_ += c.real_;
			imaginary_ += c.imaginary_;
			return *this;
		}

		void print(std::ostream &os) const {
			os << "real:" << real_ << " imaginary:" 
				<< imaginary_;
		}
};
template <typename T>
std::ostream & operator<<(std::ostream &os, 
		const Complex<T> &c) {
	c.print(os);
	return os;
}


int main(int argc, char *argv[])
{
	Complex<int> c = 1;
	std::cout << c << std::endl;
	return 0;
}
