#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void printIntHelper(unsigned int i)
{
	if(i >= 0 && i <= 9){
		putchar('0' + i);
		return ;
	}

	printIntHelper(i / 10);
	putchar('0' + i % 10);
}

void printInt(int i)
{
	unsigned int k = i;

	if(i < 0){
		putchar('-');
		k = abs(i);
	}

	printIntHelper(k);
}

int main()
{

	int i = 1 << (sizeof(int) * 8 - 1);

	cout<<i<<endl;
	//cout<<abs(i);
	printInt(i);
	cout<<endl;
	printInt(0);

	return 0;


}
