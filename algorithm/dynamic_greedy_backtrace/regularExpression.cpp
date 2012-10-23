#include <iostream>
#include <string>
#include <assert.h>
#include <fstream>


using namespace std;
bool isMatch(const char *s, const char *expr)
{
	assert(s != NULL && expr != NULL);
	if(*expr == '\0')
		return *s == '\0';

	if(*expr == '.'){
		if(*(expr+1) == '*'){
			do{
				if(isMatch(s, expr+2))
					return true;
			}while(*s++ != '\0');
			return false;
		}else{
			if(*s != '\0')
				return isMatch(s+1, expr+1);
			return false;
		}
	}else{
		if(*(expr + 1) == '*'){
			if(isMatch(s, expr+2))
				return true;
			while(*s == *expr){
				if(isMatch(s+1, expr+2))
					return true;
				s++;
			}
			return false;
		}else{
			if(*s == *expr)
				return isMatch(s + 1, expr + 1);
			return false;
		}
	}
}
bool isMatch2(const char *s, const char *expr)
{
	assert(s != NULL && expr != NULL);

	if(*expr == '\0')
		return *s == '\0';
	if(*(expr + 1) == '*'){
		if((*s == *expr || (*expr == '.' && *s != '0')) && isMatch2(s+1, expr))
			return true;
		return isMatch2(s, expr+2);
	}

	if(*expr == '.'){
		if(*s != '\0' && isMatch2(s+1, expr + 1))
			return true;
		return false;
	}

	if(*s == *expr && isMatch2(s + 1, expr + 1))
		return true;
	return false;
}

int main()
{
	const char *p = "aaba";
	const char *expr = "ab*a*c*a";
	const char *expr2 = "abc*d";




	cout<<isMatch(p, expr)<<endl;
	cout<<isMatch(p, expr2)<<endl;
	cout<<isMatch2(p, expr)<<endl;
	cout<<isMatch2(p, expr2)<<endl;
	return 0;
}
