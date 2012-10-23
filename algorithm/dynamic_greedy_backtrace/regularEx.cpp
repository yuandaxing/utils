#include <assert.h>
#include <iostream>
bool isMatch(const char *src, int sstart, const char *pattern, int pstart) {
	if(src[sstart] == '\0' && pattern[pstart] == '\0')
		return true;
	//there is a special case 'c*' match 0 character
	if(pattern[pstart] != '\0' && pattern[pstart + 1] == '*' && src[sstart] == '\0')
		return true;
	if(src[sstart] == '\0' || pattern[pstart] == '\0')
		return false;
		
	if(pattern[pstart + 1] == '*'){
		//*  match 0 character
		if(isMatch(src, sstart, pattern, pstart + 2))
			return true;
		// match 1 or more character
		if (pattern[pstart] == '.' || src[sstart] == pattern[pstart]) 
			return isMatch(src, sstart + 1, pattern, pstart);
		return false;
	} else {
		if(pattern[pstart] == '.' || src[sstart] == pattern[pstart])
			return isMatch(src, sstart + 1, pattern, pstart + 1);
		return false;
	}
	return false;
}
//we donot support the pattern start with '*' character
bool isMatch(const char *src, const char *pattern) {
     return isMatch(src, 0, pattern,0);
}


int main()
{
    assert(isMatch( "aa", "a") == false);
    assert(isMatch( "aa" ,"aa") == true );
    assert(isMatch("aaa" ,"aa") == false);
    assert(isMatch("aa", "a*") == true);
    assert(isMatch("aa", ".*") == true);
    assert(isMatch("ab", ".*") == true);
    assert(isMatch("aab", "c*a*b") == true);
    return 0;
}
