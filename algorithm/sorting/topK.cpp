#include <iostream>
#include <algorithm>
#include <assert.h>
#include <stdio.h>


int partition(int A[], int p, int q)
{
	
	if(q <= p)
		return p;

	int tmp = A[p];
	int pos = p + 1;

	for(int i = pos; i <= q; i++){
		if(A[i] <= tmp)
			std::swap(A[i], A[pos++]);
	}
	std::swap(A[p], A[pos - 1]);
	return pos - 1;
}

int partition2(int A[], int p, int q)
{
	int tmp = A[p]; //left is no bigger than tmp
	int save = p;
	if(q <= p)
		return p;
	p++;

	while(p <= q){
		while(p <= q && A[p] <= tmp) p++;
		while(p <= q && A[q] > tmp) q--;
		if(p < q){
			std::swap(A[p], A[q]);
			p++, q--;
		}
	}
	std::swap(A[save], A[p - 1]);
	return p - 1;
}

void topK(int A[], int len, int k)
{
	int left = 0, right = len - 1;
	assert(k >= 1 && k <= len);
	while(true){
		int r = partition2(A, left, right);
		if(r == k - 1)
			return ;
		if(r > k - 1){
			right = r - 1;
		}else{
			left = r + 1;
		}
	}
}

int main()
{
	int B[] = {
		0, 50, 3, 9, 7, 2, 20, 1, -7, 8, 9, -6, 20, -100, 3, 30, 70
	};

	const int len = sizeof(B) / sizeof(B[0]);

	topK(B, len, len - 5);
	for(int i = 0; i < len; i++)
		std::cout<<B[i]<<"\t";
	std::cout<<std::endl;
	return 0;
}
