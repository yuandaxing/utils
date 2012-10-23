/*
 * =====================================================================================
 *
 *       Filename:  numBytes.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月09日 16时31分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include <iostream>
#include <string>
void printKHelper(std::string &s, int K, int start, bool first) {
	if(K == 0) {
		std::cout << s << "\t";
		return ;
	}
	if( !first )
	{
		s[start] = '0';
		printKHelper(s, K - 1, start + 1, false);
	}
	for(int i = 1; i < 10; i++) {
		s[start] = '0' + i;
		printKHelper(s, K - 1, start + 1, false);
	}

}
void printKbytesNumber(int K) {
	for(int i = 1; i <= K; i++) {
		std::string s(i, '0');
		printKHelper(s, i, 0, true);
	}
}

int main ( int argc, char *argv[] )
{
	printKbytesNumber(3);
	std::cout << std::endl;
	return 0;
}				/* ----------  end of function main  ---------- */
