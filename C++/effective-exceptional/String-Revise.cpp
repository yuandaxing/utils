/*
 * =====================================================================================
 *
 *       Filename:  String-Revise.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月08日 15时16分14秒
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
#include <string.h>
using namespace std;
struct ci_char_traits : public char_traits<char>
						//just inherit all the other functions
						//  that we don't need to override
{
	static bool eq( char c1, char c2 )
	{ return toupper(c1) == toupper(c2); }

	static bool ne( char c1, char c2 )
	{ return toupper(c1) != toupper(c2); }

	static bool lt( char c1, char c2 )
	{ return toupper(c1) <  toupper(c2); }

	static int compare( const char* s1,
			const char* s2,
			size_t n ) {
		for( size_t i = 0 ; i < n ; i++ )
		{
			if( !eq(s1[i], s2[i]) )
			{
				return s1[i] - s2[i];
			}
		}
		return 0;
	}
};

typedef basic_string<char, ci_char_traits> ci_string;
int main(int argc, char *argv[])
{
	ci_string cstr1 = "Fuck";
	ci_string cstr2 = "fuck";

	std::cout << (cstr1 == cstr2) << std::endl;

	std::string str1 = "fuck", str2 = "FUck";
	std::cout << (str1 == str2) << std::endl;

	std::cout << cstr1.c_str() << std::endl;
	return 0;
}
