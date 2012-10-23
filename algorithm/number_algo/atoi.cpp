/*
 * =====================================================================================
 *
 *       Filename:  atoi.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月08日 16时57分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <assert.h>
//int atoi(const char *str, bool &valid)
//do not consider overflow
bool auxilary_atoi(const char *str, int &val/*, bool overflow*/)
{
	bool positive = true;
	while(*str == ' ' || *str == '\t')
		str++;
	//determine signal
	if(*str == '-'){
		positive = false;
		str++;
	} else if(*str == '+') {
		positive = true;
		str++;
	}

	if(isdigit(*str) == false)
		return false;
	val = 0;
	while(isdigit(*str)) {
		val = val * 10 + *str - '0';
		str++;
	}
	if(positive == false)
		val = -val;
	return true;
}
int main ( int argc, char *argv[] )
{
	int val;
	assert(auxilary_atoi(" 123    ", val));
	assert(val == 123);
	assert(auxilary_atoi(" -123-------", val));
	assert(val == -123);
	assert(auxilary_atoi(" -123456789-------", val));
	assert(val == -123456789);
	return 0;
}				/* ----------  end of function main  ---------- */
