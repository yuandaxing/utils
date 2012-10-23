#include <iostream>
#include <string>
#include <assert.h>
using namespace std;


string DP(string &a)
{
	int lena = a.size();
	
	char **matrix = new char *[lena];
	for(int i = 0; i < lena; i++){
		matrix[i] = new char[lena];
	}

	for(int i = 0; i < lena; i++){
		for(int j = 0; j < lena; j++){
			matrix[i][j] = 0;
		}
	}

	int maxLen = 0;
	int start = -1;
	bool found = false;
	for(int len = 1; len <= lena; len++){
		for(int i = 0; i <= lena - len; i++){
			if(a[i] == a[i + len - 1]){
				found = false;
				if(len == 1 || len == 2){
					matrix[i][i + len - 1] = 1;
					found = true;
				}else{
					if(matrix[i + 1][i + len - 2] == 1){
						matrix[i][i + len - 1] = 1;
						found = true;
					}
				}
				if(found && maxLen < len){
					maxLen = len;
					start = i;
				}
			}

		}
	}

	for(int i = 0; i < lena; i++)
		delete matrix[i];
	delete[] matrix;

	if(maxLen == 0)
		return string();
	return a.substr(start, maxLen);
}

int expandAroundMiddle(const string &s, int left, int right)
{
	int len = s.size();

	assert(left >= 0 && left < len);
	assert(right >= 0 && right < len);

	while(left >= 0 && right < len && s[left] == s[right]){
		left--, right++;
	}

	return right - left - 1;
}

string longestPalindromeSimple(string &s)
{
	int start = -1, longest = 0;
	int first, second;
	int start1, start2;

	int len = s.size();
	for(int i = 0; i < len - 1; i++){
		first = expandAroundMiddle(s, i, i);
		start1 = i - (first - 1) / 2;
		if(first > longest){
			longest = first;
			start = start1;
		}
		second = expandAroundMiddle(s, i, i + 1);
		start2 = i - second / 2 + 1;
		if(second > longest){
			longest = second;
			start = start2;
		}
	}

	if(longest == 0 && s.size() >  0){
		longest = expandAroundMiddle(s, s.size() - 1, s.size() - 1);
		start = s.size() - 1;
	}

	return s.substr(start, longest);
}
string preProcess(string str)
{
	string sp("^");
	int len = str.size();

	for(int i = 0; i < len; i++){
		sp.push_back('#');
		sp.push_back(str[i]);
	}

	sp.push_back('#');
	sp.push_back('$');
	return sp;
}

/*
*http://www.leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
*/
string longestPalindrome(string str)
{
	string sp = preProcess(str);
	int n = sp.size();
	int *p = new int[n];
	int center = 0, R = 0;

	for(int i = 1; i < n - 1; i++){
		int mirror = 2 * center - i;
		p[i] = R > i ? min(p[mirror], R - i) : 0 ;

		// we try to expand the center in i
		 while (sp[i + 1 + p[i]] == sp[i - 1 - p[i]])
			       p[i]++;
		 if(i + p[i] > R){
			 center = i;
			 R = i + p[i];
		 }

	}
	int maxLen = 0;
	int centerIndex = 0;
	for(int i = 1; i < n - 1; i++){
		if(p[i] > maxLen){
			maxLen = p[i];
			centerIndex = i;
		}
	}

	for(int i = 1; i < n - 1; i++){
		cout<<p[i]<<"\t";
	}
	cout<<endl;
	delete []p;
	return str.substr((centerIndex - 1 - maxLen)/2, maxLen);
}



int main()
{
	string str = string("abacdgfdcaba");
	string str1 = string("caba");
	string str2 = "babcbabcbaccba";
	string str3 = "a";
	cout<<DP(str)<<endl;
	cout<<DP(str1)<<endl;
	cout<<longestPalindromeSimple(str1)<<endl;
	cout<<longestPalindromeSimple(str)<<endl;
	cout<<longestPalindrome(str2)<<endl;
	cout<<longestPalindrome(str3)<<endl;
	return 0;
}
