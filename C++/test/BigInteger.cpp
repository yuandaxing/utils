#include <iostream>
#include <vector>
#include <assert.h>
#include <cmath>
#include <utility>

class UnsignBigInteger {
	private:
		std::vector< char > i_; 
		void compact() {
			int count = 0;
			for( int i = i_.size() - 1; i >= 0; i-- )
				if( i_[i] == 0 ) 
					count++;
				else
					break;
			//resize dose not change storage capacity directly
			i_.resize( i_.size() - count );
		}   
		void expand10( int k ) { 
			int curSize = i_.size();
			int expandSize = curSize + k;
			i_.resize( expandSize, 0 );
			copy_backward( i_.begin(), i_.begin() + curSize, 
					i_.end() );
			fill_n( i_.begin(), k, 0 );
		}   
		void add( const UnsignBigInteger &other ) { 
			int max = std::max( i_.size(), other.i_.size() );
			//to reserve one more place, so it is enough to hold sum    
			i_.resize( max + 1, 0 );  
			int c = 0;

			for( unsigned i = 0; i < i_.size(); i++ ) { 
				int value = i_[i] + c ; 
				if( i < other.i_.size() )
					value += other.i_[i];
				i_[i] = value % 10; 
				c = value / 10; 
			}   
		}  
		void sub( const UnsignBigInteger &o ) { 
			if( o.bigThan(*this) ) { 
				std::cout << "the other must small then current" << std::endl;
				return ;
			}
			int b = 0;
			for( unsigned i = 0; i < i_.size(); i++ ) {
				i_[i] -= b;
				if( i < o.i_.size() )
					i_[i] -= o.i_[i];

				if( i_[i] < 0 ) {
					i_[i] += 10;
					b = 1;
				} else {
					b = 0;
				}
			}
			compact();
		}
		void mul( int m ) {
			assert( m >= 0 && m < 10 );
			i_.resize( i_.size() + 1, 0 );
			int c = 0;
			for( unsigned i = 0; i < i_.size(); i++ ) {
				int value = i_[i] * m + c;
				i_[i] = value % 10;
				c = value / 10;
			}
		}
		const char & operator[]( int i ) const {
			return i_[i];
		}
		int size() const { return i_.size(); }
	public:
		bool bigThan( const UnsignBigInteger &o ) const {
			if( i_.size() != o.i_.size() )
				return i_.size() > o.i_.size();

			for( unsigned i = i_.size() - 1; i >= 0; i-- )
				if( i_[i] != o.i_[i] )
					return i_[i] > o.i_[i];

			return false;
		}
		void print(std::ostream &out) const {
			for( int i = i_.size() - 1; i >= 0; i-- )
				out << static_cast< int >( i_[i] );
		}

		//we must stop the implicit conversion
		explicit UnsignBigInteger( const std::string & nums ) :
			i_(nums.size(), 0){
				for( unsigned i = 0; i < nums.size(); i++ )
					i_[i_.size() - 1 - i] = nums[i] - '0';
			}

		explicit UnsignBigInteger( int n ) :
			i_(0){
				int v = n;

				while( v != 0 ) {
					i_.push_back( v % 10 );
					v /= 10;
				}
			}

		UnsignBigInteger() : i_(0) { }

		friend UnsignBigInteger& operator+=( UnsignBigInteger &lhs, const UnsignBigInteger &rhs );
		friend UnsignBigInteger& operator-=( UnsignBigInteger &lhs, const UnsignBigInteger &rhs );
		friend UnsignBigInteger operator-( const UnsignBigInteger &lhs, const UnsignBigInteger &rhs );
		friend UnsignBigInteger operator+( const UnsignBigInteger &lhs, const UnsignBigInteger &rhs );
		friend UnsignBigInteger operator*( const UnsignBigInteger &lhs, const UnsignBigInteger &rhs );
		friend std::ostream & operator<<( std::ostream &out, const UnsignBigInteger &b );
		friend UnsignBigInteger  power( const UnsignBigInteger &b, int e );
		friend std::pair<UnsignBigInteger, UnsignBigInteger> div( const UnsignBigInteger &lhs, const UnsignBigInteger &rhs);
		friend UnsignBigInteger operator/( const UnsignBigInteger &lhs, const UnsignBigInteger &rhs );
		friend UnsignBigInteger mod( const UnsignBigInteger &lhs, const UnsignBigInteger &rhs );
};


UnsignBigInteger& operator+=( UnsignBigInteger &lhs, const UnsignBigInteger &rhs ) {
	lhs.add( rhs );
	lhs.compact();
	return lhs;
}
UnsignBigInteger operator+( const UnsignBigInteger &lhs, const UnsignBigInteger &rhs ) {
	UnsignBigInteger tmp;
	tmp += lhs;
	tmp += rhs;
	tmp.compact();
	return tmp;
}
UnsignBigInteger& operator-=( UnsignBigInteger &lhs, const UnsignBigInteger &rhs ) {
	lhs.sub( rhs );
	return lhs;
}

UnsignBigInteger operator-( const UnsignBigInteger &lhs, const UnsignBigInteger &rhs ) {
	UnsignBigInteger ret( lhs );
	ret.sub( rhs );
	return ret;
}
UnsignBigInteger operator*( const UnsignBigInteger &lhs, const UnsignBigInteger &rhs ) {
	UnsignBigInteger ret;

	for( int i = 0; i < rhs.size(); i++ ) {
		UnsignBigInteger tmp( lhs );
		tmp.mul( rhs[i] );
		tmp.expand10( i );
		ret += tmp;
	}
	ret.compact();
	return ret;
}

std::pair<UnsignBigInteger, UnsignBigInteger> div( const UnsignBigInteger &lhs, const UnsignBigInteger &rhs) {
	UnsignBigInteger u1(lhs), u2(rhs), ret;

	while( !u2.bigThan(u1) ) {
		unsigned s1 = u1.size(), s2 = u2.size();
		unsigned diff = s1 - s2;
		UnsignBigInteger temp(u2);
		temp.expand10(diff);

		if( temp.bigThan(u1) )
			diff--;

		UnsignBigInteger temp2(u2);
		temp2.expand10(diff);
		//i use a very naive way to calculate the most significant of the result
		int count = 0;
		while( !temp2.bigThan(u1) ) {
			u1 -= temp2;
			count++;
		}

		//accumulate the result
		UnsignBigInteger cur( count );
		cur.expand10( diff );
		ret += cur;
		u1.compact();
	}
	return std::pair<UnsignBigInteger, UnsignBigInteger>(ret, u1);

}
UnsignBigInteger operator/( const UnsignBigInteger &lhs, const UnsignBigInteger &rhs ) {
	return div( lhs, rhs ).first;
}

std::ostream & operator<<( std::ostream &out, const UnsignBigInteger &b ) {
	b.print( out );
	return out;
}

UnsignBigInteger mod( const UnsignBigInteger &lhs, const UnsignBigInteger &rhs ) {
	return div( lhs, rhs ).second;
}
//tail recursion, how to eliminate?
UnsignBigInteger  power( const UnsignBigInteger &b, int e ) {

	if( e == 0 )
		return UnsignBigInteger( 1 );
	else if( (e & 1) == 1 )
		return b * power( b, e - 1 );
	else {
		UnsignBigInteger tmp = power( b, e / 2 );
		return tmp * tmp;
	}
}

class SignBigInteger {
	private:
		bool sign_;
		UnsignBigInteger unbi_;
	public:
		SignBigInteger( const std::string &s, bool p = true) : sign_(p), unbi_(s) { };
		SignBigInteger(): sign_(true) { }
		friend SignBigInteger operator-( const SignBigInteger &s );
		friend SignBigInteger& operator+=( SignBigInteger &lhs, const SignBigInteger &rhs );
		friend SignBigInteger& operator-=( SignBigInteger &lhs, const SignBigInteger &rhs );
		friend SignBigInteger operator-( const SignBigInteger &lhs, const SignBigInteger &rhs );
		friend SignBigInteger operator+( const SignBigInteger &lhs, const SignBigInteger &rhs );
		friend SignBigInteger operator*( const SignBigInteger &lhs, const SignBigInteger &rhs );
		friend std::ostream & operator<<( std::ostream &out, const SignBigInteger &b );
		friend SignBigInteger  power( const SignBigInteger &b, int e );
		friend std::pair<SignBigInteger, SignBigInteger> div( const SignBigInteger &lhs, const SignBigInteger &rhs);
		friend SignBigInteger operator/( const SignBigInteger &lhs, const SignBigInteger &rhs );
		friend SignBigInteger mod( const SignBigInteger &lhs, const SignBigInteger &rhs );
};

SignBigInteger operator-( const SignBigInteger &s ) {
	SignBigInteger temp( s );
	temp.sign_ = !temp.sign_;
	return temp;
}
SignBigInteger& operator+=( SignBigInteger &lhs, const SignBigInteger &rhs ) {
	if( lhs.sign_ == rhs.sign_ ) {
		lhs.unbi_ += rhs.unbi_;
	} else {
		if( lhs.unbi_.bigThan( rhs.unbi_ ) ) {
			lhs.unbi_ -= rhs.unbi_;
		} else {
			lhs.unbi_ = rhs.unbi_ - lhs.unbi_;
			lhs.sign_ = rhs.sign_;
		}
	}
	return lhs;
}
SignBigInteger& operator-=( SignBigInteger &lhs, const SignBigInteger &rhs ) {
	return lhs += (- rhs);
}
SignBigInteger operator-( const SignBigInteger &lhs, const SignBigInteger &rhs ) {
	SignBigInteger temp(lhs);
	return temp -= rhs;
}
SignBigInteger operator+( const SignBigInteger &lhs, const SignBigInteger &rhs ) {
	SignBigInteger temp( lhs );
	return temp += rhs;
}
SignBigInteger operator*( const SignBigInteger &lhs, const SignBigInteger &rhs ) {
	SignBigInteger sb;
	if( lhs.sign_ == rhs.sign_ )
		sb.sign_ = true;
	else
		sb.sign_ = false;

	sb.unbi_ = lhs.unbi_ * rhs.unbi_;
	return sb;
}
std::ostream & operator<<( std::ostream &out, const SignBigInteger &b ) {
	if( b.sign_ == false )
		out << "-";
	out << b.unbi_;
	return out;
}
SignBigInteger  power( const SignBigInteger &b, int e ) {
	SignBigInteger sb;
	sb.sign_ = b.sign_;
	if( (b.sign_ == false) && ((e & 1) == 0) )
		sb.sign_ = true;

	sb.unbi_ = power( b.unbi_, e );
	return sb;
}

int main() {
	UnsignBigInteger b1("12312345678901023456");
	UnsignBigInteger b2("4561233123123123123123");
	UnsignBigInteger b3(123);
	UnsignBigInteger b4(321);
	std::cout << b1 + b2 << std::endl;
	std::cout << b1 * b2 << std::endl;

	std::cout << b3 << std::endl;
	std::cout << b1 * b3 << std::endl;

	std::cout << power( b3, 2 ) << std::endl;
	std::cout << power( b3, 1100 ) << std::endl;

	std::cout << b4 - b3 << std::endl;
	std::cout << b2 - b1 << std::endl;

	std::cout << b4 / b3 << std::endl;
	std::cout << b2 / b1 << std::endl;
	std::cout << mod( b2, b1 ) << std::endl;
	std::cout << mod( b4, b3 ) << std::endl;


	SignBigInteger sb1("12345", false), sb2("123");

	std::cout << power(sb1, 20) << std::endl;
	std::cout << sb1 * sb2 << std::endl;
	return 0;
}

