#include <iostream>
#include <string.h>

int count(const char *str)
{
	if(str == NULL)
		return 0;

	int count = 0;
	bool begin = false;

	while(*str != '\0'){
		if(!begin && isalpha(*str)){
			begin = true;
			count++;
		}

		if(!isalpha(*str))
			begin = false;

		str++;
	}
	return count;
}
int count2(const char *text)
{
	if(text == NULL)
		return 0;

	int count = 0;
	bool inword = false;

	while(*text){
		if(inword == false && isalpha(*text)){
			count++;
			inword = true;
		}else if(!isalpha(*text)){
			inword = false;
		}
		text++;
	}
	return count;
}


int main()
{
	using namespace std;
	const char *str = "haha        xxxxxxxxxxxxx 1aaaa2ccccckkkk.bc";
	char tmp[100];
	strcpy(tmp, str);
	cout<<count(tmp)<<endl;
	cout<<count2(tmp)<<endl;
	return 0;
}
