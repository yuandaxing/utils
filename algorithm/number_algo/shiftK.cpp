#include <iostream>

void shift1(int A[], int len)
{
	if(len < 1)
		return ;	
	int tmp = A[len - 1];
	for(int i = len - 1; i >= 1; i--)
		A[i] = A[i - 1];
	A[0] = tmp;
}
void shiftK1(int A[], int len, int k)
{
	if(len <= 1)
		return ;
	k = k % len;
	for(int i = 0; i < k; i++)
		shift1(A, len);
}

void reverse(int A[], int len)
{
	for(int left = 0, right = len - 1; right > left; 
			right--, left++){
		int tmp = A[right];
		A[right] = A[left];
		A[left] = tmp;
	}
}

void shiftK2(int A[], int len, int k)
{
	if(len <= 1)
		return ;
	k = k % len;
	reverse(A, len);
	reverse(A, k);
	reverse(A + k, len - k);
}


void printArray(int A[], int len)
{
	using namespace std;
	for(int i = 0; i < len; i++)
		cout<<A[i]<<"\t";
	cout<<endl;
}
void copyArray(int A[], int len, int B[])
{
	for(int i = 0; i < len; i++)
		B[i] = A[i];
}

//void shiftK3(int A[], int len, int k)
//{
//	if(len < 1)
//		return ;
//	int start = len - 1 + k;
//	int j;
//
//	k = k % len;
//
//	for(int i = 0; i < k; i++){
//		int tmp = A[(start - i) % len];
//		for(j = start - i; j > 2 *k; j -= k){
//			A[j % len] = A[(j - k) % len];
//		}
//		A[j % len] = tmp;
//	}
//}
int main()
{
	int A[] = {
		1, 2, 3, 4, 5, 6, 7
	};
	const int len = sizeof(A) / sizeof(A[0]);
	int B[len];

	copyArray(A, len, B);
	shiftK1(B, len, 3);
	printArray(B, len);


	copyArray(A, len, B);
	shiftK1(B, len, 7);
	printArray(B, len);



	copyArray(A, len, B);
	shiftK1(B, len, 8);
	printArray(B, len);




	copyArray(A, len, B);
	shiftK2(B, len, 3);
	printArray(B, len);


	copyArray(A, len, B);
	shiftK2(B, len, 7);
	printArray(B, len);



	copyArray(A, len, B);
	shiftK2(B, len, 8);
	printArray(B, len);



//	copyArray(A, len, B);
//	shiftK3(B, len, 2);
//	printArray(B, len);
//
//
//
//	copyArray(A, len, B);
//	shiftK3(B, len, 7);
//	printArray(B, len);
//	return 0;

}
