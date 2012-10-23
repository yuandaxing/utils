#include <iostream>
#include <stdint.h>


using namespace std;

uint32_t reverse(uint32_t inte)
{
	int i = 0, j = 31;
	while(i < j){
		int left = (inte >> i) & 1;
		int right = (inte >> j) & 1;
		if(left != right){
			inte ^= ((1 << i) | (1 <<  j));
		}
		i++, j--;
	}
	return inte;
}
void printBit(uint32_t inte)
{
	for(int i = 0; i < 32; i++)
		cout<< ((inte >> (32 - i - 1)) & 0x1) <<" ";
	cout<<endl;
}
int main()
{
	printBit(0xfabcabc);
	printBit(reverse(0xfabcabc));
}
