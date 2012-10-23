/*
 * =====================================================================================
 *
 *       Filename:  KMP.cpp
 *
 *    Description: K M P processing the pattern string, and suffix tree preprocess
 *    the source string, this maybe not the same 
 *
 *        Version:  1.0
 *        Created:  2012年09月17日 20时18分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <vector>
#include <string>
#include <iostream>
#include "../../Common.h"

void Next(const std::string &pattern, std::vector<int> &next) ;
int Idx_KMP(const std::string &src, const std::string &pattern, 
		std::vector<int> &next, int pos) ;
void Next_better(const std::string &pattern, 
		std::vector<int> &next) ;

std::vector<int> KMP(const std::string &src, 
		const std::string &pattern) {
	std::vector<int> array(pattern.size(), 0), pos;
	unsigned int cur = 0;

	//this case 
	if(pattern.size() == 0) {
		return pos;
	}

	Next_better(pattern, array);
	while( cur != std::string::npos ) {
		cur = Idx_KMP(src, pattern, array, cur);
		if( cur != std::string::npos )
		{
			pos.push_back(cur);
			cur++;
		}
	}
	return pos;
}

void Next(const std::string &pattern, std::vector<int> &next) {

	next.resize(pattern.size());
	next[0] = -1;
	int i = 0, j = -1;
	while(static_cast<unsigned>(i) < pattern.size() - 1) {
		if(j == -1 || pattern[i] == pattern[j]) {
			i++;
			j++;
			next[i] = j;
		} else {
			j = next[j];
		}
	}
}
void Next_better(const std::string &pattern, 
		std::vector<int> &next) {

	next.resize(pattern.size());
	next[0] = -1;
	int i = 0, j = -1;
	while(static_cast<unsigned>(i) < pattern.size() - 1) {
		if(j == -1 || pattern[i] == pattern[j]) {
			i++;
			j++;
			if(pattern[i] != pattern[j])
				next[i] = j;
			else
				next[i] = next[j];
		} else {
			j = next[j];
		}
	}

	std::cout << next<< std::endl;
}
int Idx_KMP(const std::string &src, const std::string &pattern, 
		std::vector<int> &next, int pos) {
	int i = pos, j = 0;
	while(static_cast<unsigned>(i) < src.size() &&
		   	j < static_cast<signed>(pattern.size())) {
		if(j == -1 || src[i] == pattern[j]) {
			i++;
			j++;
		} else {
			j = next[j];
		}
	}
	if( static_cast<unsigned>(j) == pattern.size() )
	{
		return i - j;
	}
	return std::string::npos;
}

int main(int argc, char *argv[])
{
	std::string pattern = "abaabc",
		src = "acabaabaabcacaabc";

	std::vector<int> pos = KMP(src, pattern);

	std::cout << pos << std::endl;

	std::string pattern1 = "aaaab",
		src1 = "aaabaaaab";

	pos = KMP(src1, pattern1);
	std::cout << pos << std::endl;
	return 0;
}
