#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

#include <sstream>
#define ISSPACE(x) ((x)==' '||(x)=='\r'||(x)=='\n'||(x)=='\f'||(x)=='\b'||(x)=='\t')

char * rightTrim(char *str)
{
	int len = strlen(str);
	while(--len>=0) {
		if(ISSPACE(str[len])) {
			str[len] = '\0';
		} else {
			break;
		}
	}
	return str;
}

char * getInputLine(char *buffer, int length)
{
	if(fgets(buffer,length, stdin)==NULL) {
		return NULL;
	}
	rightTrim(buffer);
	if(strlen(buffer)<=0) {
		return NULL;
	}
	return buffer;
}

int extractNumbersToArray(char *str, int *numbers)
{
	const char *split = ",";
	char *p = strtok (str,split);
	int index = 0;
	while(p!=NULL) {
		numbers[index++] = atoi(p);
		p = strtok(NULL,split);
	}
	return index;
}

using namespace std;
void trim(string &str) {
		str.erase(str.find_last_not_of("\n\r \t") + 1);
		str.erase(0, str.find_first_not_of("\n\r\t"));
}
bool apply(string s, int v) {
	int idx = s.find_first_of("0123456789");
	int k;
	string n(&s[idx -1], &s[s.size()]);
	istringstream is(n);
	is >> k;
	idx = s.find_first_of(">=<");
	if(s[idx] == '>')
		return v > k;
	if(s[idx] == '=')
		return v == k;
	if(s[idx] == '<')
		return v < k;
	return false;
}
bool helper(int k, string s) {
	int idx = s.find_first_of("o");

	if(static_cast<unsigned>(idx) == string::npos) {
		int n = 0;
		int pre = 0;
		while(static_cast<unsigned>(n) != string::npos) {
			int cur = s.find_first_of("n", pre);
			int len = cur - 1 - pre;
			if(static_cast<unsigned>(cur) == string::npos) {
				len = s.size() - cur;
			}
			string curs = s.substr(pre, len);
			trim(curs);
			if(!apply(curs, k))
				return false;
			pre = cur + 2;
			n = cur;
		}
		return true;
	}
	string s1 = s.substr(0, idx);
	string s2 = s.substr(idx + 2);
	trim(s1), trim(s2);
	return helper(k, s1) || helper(k, s2);
}
void determineRuleAndOutput(int *numbers, int numberCount, char ** rules, int ruleCount)
{
	for( int i = 0 ; i < ruleCount; i++ )
	{
		int result = true;
		string temp(rules[i]);
		trim(temp);
		int idx = temp.find_first_of(" ");
		int idx2 = temp.find_first_of(" ", idx + 1);
		string s1 = temp.substr(0, idx), s2 = temp.substr(idx2);
		trim(s1), trim(s2);
		for( int j = 0 ; j < numberCount; j++ )
		{
			if(!helper(numbers[j],s2)){
				result = false;
				break;
			}
		}
		if(result)
			cout << s1;;
	}
//your code here
}

int main(int argc, char ** argv)
{
	int numbers[1024];
	char numberBuffer[1024];
	getInputLine(numberBuffer, 1024);
	int numberCount = extractNumbersToArray(numberBuffer, numbers);
	char buffers[1024][1024];
	char *rules[1024];
	int ruleCount = 0;
	while(getInputLine(buffers[ruleCount], 1024) != NULL) {
		rules[ruleCount] = buffers[ruleCount];
		ruleCount++;
	}
	determineRuleAndOutput(numbers, numberCount, rules, ruleCount);
	return 0;
}

