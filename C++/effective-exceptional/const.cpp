/*
 * =====================================================================================
 *
 *       Filename:  const.cpp
 *
 *    Description:  test for const and enum
 *
 *        Version:  1.0
 *        Created:  2012年05月02日 10时36分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yuan DaXing (http://hi.baidu.com/%E8%A2%81%E5%A4%A7%E6%98%9F/home), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

#define ASPECT_RATIO	1.635

const double Aspect_ration = 1.653;
const char * const authorName = "Scott Meyers";
const std::string author("Scott Meyers");

class GamePlayer {
	private:
		static const int NumTurns = 5;
		int score[NumTurns];
		enum { TestNum = 10 };
		int s[TestNum];
	public:
		friend std::ostream & operator<<(std::ostream &os, 
				const GamePlayer &gp) {
				os << gp.NumTurns << gp.TestNum;
				return os;
		}
};

template<typename T>
inline T Max(const T &a, const T &b) {
	return a > b ? a : b;
}

class _string{
	private:
		std::string v;
		mutable int count;
	public:
		const std::string & getv() const {
			count++;
			return v;
		}	

		const int getcount() const {
			count++;
			return count;
		}
		_string(const std::string &str): v(str), count(0) { }
		friend const _string operator*(const _string & lhs, const _string &rhs) {
			return _string(lhs.v + rhs.v);
		}

		friend std::ostream & operator<<(std::ostream &out, const _string &str) {
			out << str.v ;
			return out;
		}

		char & operator[](std::size_t position) {
			return const_cast<char &> (
				static_cast<const _string>(*this)
					[position]
					);		
		}

		const char & operator[](std::size_t position) const {
			return v[position];
		}
};
const int GamePlayer::NumTurns;

int main()
{
	int a[] = {1, 2, 3, 4, 5, 6};
	const int alen = sizeof(a) / sizeof(a[0]);
	GamePlayer gp;
	std::cout << gp << "Author:" << author << " authorName" << authorName << std::endl;
	std::vector<int> vi(a, a + alen);
	std::vector<int>::iterator iter = vi.begin();
	std::vector<int>::const_iterator citer = vi.begin();
	citer++;
	//citer = 10;

	*iter = 20;
	std::cout << *iter << std::endl;

	std::cout << "max:" << Max(2, 3) << std::endl;

	std::cout << "_string(test1) * _string(test2) :" 
		<< _string("test1") * _string("test2") << std::endl;

	const _string t("test3="); 
	_string f("what");
	f[0] = 'f';
	std::cout << t.getv() << std::endl;
	std::cout << t.getcount() << std::endl;
	std::cout << "f[0]:" << f[0] << std::endl; 
	return 0;
}
