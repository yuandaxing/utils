#include <iostream>
#include <string>
#include <stdint.h>
using namespace std;



unsigned long long string_to_unlong(string a)
{
	unsigned long long result = 0;
	int length = a.size();
	for(int i = 0; i<length; i++)
	{
		result = (a[i] - '0') + result * 10;
	}
	return result + 1;
}

bool compareString(string a, string b)
{
	int diff = a.size() - b.size();
	return a.substr(diff, a.size()) >= b;
}




int main()
{
	unsigned int n;
	string x, a, b;
	uint64_t result, suma = 0, sumb = 0;
	cin>>n;
	for(unsigned int i = 0; i<n; i++)
	{
		cin>>x>>a>>b;

		int  diff = 0;
		string tmp = b;
		diff = b.size() - x.size();

		if(x.size() > b.size())
			sumb = 0;
		else{
			sumb = string_to_unlong(tmp.erase(diff, b.size()));
			if(!compareString(b, x))
				sumb--;
		}

		diff = a.size() - x.size();
		tmp = a;
		if(x.size() > a.size())
			suma = 0;
		else{
			suma = string_to_unlong(tmp.erase(diff, a.size()));
			if(!compareString(a, x))
				suma--;
		}

		if(a.size() < x.size() || a.substr(diff, a.size())<x)
			result = sumb - suma;
		else
			result = sumb - suma + 1;

		cout<<result<<endl;

	}

	return 0;

}
