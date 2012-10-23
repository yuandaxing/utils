#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
/*
   really it is trivial to consider about negative
   especially the integer is 1000 0000 0000 0000
   */
int reverse(int r)
{
		assert(r >= 0);
		int rev = 0;
		while(r != 0){
			rev = rev * 10 + r % 10;
			r /= 10;
		}
		return rev;
}
bool isParlidrom(int n)
{
	if(n < 0)
		return false;
	else
		return n == reverse(n);
}
bool isParlidrom2(int n)
{
	if(n < 0)
		return false;
	if(n == 0)
		return true;
	int div = 1;
	while(div <= n / 10)
		div *= 10;

	while(n != 0){
		int left = n / div;
		int right = n % 10;
		if(left != right)
			return false;
		n = n % div / 10;
		div /= 100;
	}
	return true;
}
using namespace std;
int main()
{
	int i = abs(INT_MIN);
	cout<<i<<endl;
	assert(isParlidrom(0));
	assert(!isParlidrom(-100));
	assert(isParlidrom(1122332211));
	assert(!isParlidrom(1222222223));
	assert(isParlidrom2(0));
	assert(!isParlidrom2(-100));
	assert(isParlidrom2(1122332211));
	assert(!isParlidrom2(1222222223));
	return 1;

}
