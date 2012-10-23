/*
 * =====================================================================================
 *
 *       Filename:  delCopy.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年07月01日 18时28分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <string>
#include <iostream>
#include <bitset>

void DelCopy(std::string &dest, 
		const std::string &src, const std::string &del) {
	std::bitset<128> cbs;
	int i = 0;
	for ( i = 0; static_cast<unsigned>(i) < del.size(); i += 1 ) {
		cbs.set(del[i]);
	}

	for ( i = 0; static_cast<unsigned>(i) < src.size(); i += 1 ) {
		if(cbs.test(src[i]) == false) {
			dest.append(1, src[i]);
		}
	}
}

int main ( int argc, char *argv[] )
{
	using namespace std;
	string del = "fuck";
	string src = "abcdefghigkffffffffffffsssssssssuuuuuuuuuuuuuccccccccccckkkkkkkkkkkkki";
	string dest;
	DelCopy(dest, src, del);
	cout << dest << std::endl;
	return 0;
}				/* ----------  end of function main  ---------- */
