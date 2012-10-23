/*
 * =====================================================================================
 *
 *       Filename:  compare.cpp
 *
 *    Description:  to compare
 *
 *        Version:  1.0
 *        Created:  2012年04月26日 15时31分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yuan DaXing (http://hi.baidu.com/%E8%A2%81%E5%A4%A7%E6%98%9F/home), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <cstdlib>
#include <string>
template <typename T>
inline int compare(const T &left, const T &right) {
	if(left < right)
		return -1;
	if(left > right)
		return 1;

	return 0;
}

template <typename T>
class queue{
	public:
		queue() {};
		queue(const queue &);
		T & front();
		const T & front() const;
		void push(const T &);
		void pop();
		bool empty() const;
	private:
				

};


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	std::string str1 = "fuck", str2 = "good";
	int left = 1, right = 2;
	std::cout << compare(str1, str2) << std::endl;
	std::cout << compare(left, right) << std::endl;
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
