#include <iostream>
#include <string>
using namespace std;


string lswithoutRepeat(string &s)
{
	int len = s.size();
	char tmp[128] = {
		0
	};
	int j = 0;
	int max = 0, start = 0;
	
	if(len == 0)
		return "";
	for(int i = 0; i < len; i++){
		if(tmp[(int)s[i]] == 1){
			while(s[j] != s[i]){
				tmp[(int)s[j]] = 0;
				j++;
			}
			j++;
		}else{
			tmp[(int)s[i]] = 1;
		}
		if(i - j + 1 > max){
			max = i - j + 1;
			start = j;
		}
	}
	return s.substr(start, max);

}
int main()
{
	string str = "abcabcbb";
	string str1 = "aabcd";
	string str2 = "";
	cout<<lswithoutRepeat(str)<<endl;
	cout<<lswithoutRepeat(str1)<<endl;
	cout<<lswithoutRepeat(str2)<<endl;
}
