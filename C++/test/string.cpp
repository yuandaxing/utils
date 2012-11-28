#include <iostream>
#include <string>
#include <cctype>
int main()
{
	std::string str = "what FUck";

	for(std::string::iterator iter = str.begin();
			iter != str.end(); ++iter) {
		if(isupper(*iter)) {
			str.erase(iter);
			--iter;
		}
	}
	std::cout << str;
	return 0;
}
