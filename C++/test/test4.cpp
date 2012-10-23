#include <iostream>
using namespace std;
#pragma pack (4)
class A
{
	int x:8;
	int y:4;
	double a;
	int z:2;
};
class B
{
	int x:8;
	int y:4;
	double a;
};
class C
{
	int x;
	double y;
};
int main()
{
	cout<<sizeof(long)<<endl;
	cout<<sizeof(A)<<endl;
	cout<<sizeof(B)<<endl;
	cout<<sizeof(C)<<endl;
	cout<<sizeof(double)<<endl;
}
