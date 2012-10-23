#include <iostream>
#include <math.h>
using namespace std;


int calculateSquare(int X)
{
	int right = (int)sqrt(X);
	int left = 0;
	int n = 0;

	while(right >= left){
		int remain = (int) sqrt(X - right * right);
		if(X == right * right + remain * remain)
			n++;

		left = remain + 1;
		right--;
	}
	return n;
}

int main()
{
	cout<<calculateSquare(10)<<endl;
	cout<<calculateSquare(25)<<endl;
	return 0;
}
