#include <iostream>
bool isNatureSeq(int A[], int N)
{
	if(A == NULL || N < 1)
		return true;
	
	int min = A[0], max = A[0];
	for(int i = 0; i < N; i++) {
   		if(A[i] > max)
        		max = A[i];
   		if(A[i] < min)
       			min = A[i];
	}

	if(N != max - min + 1)
   		return false;

	for(int i = 0; i < N; i++) {
		int pos = A[i] -  min;
  		while(pos != i) {
   			if(A[pos] == A[i])
      				return false;
   			std::swap(A[i], A[pos]);
   			pos = A[i] - min;
		}
	}

	return true;
}

int main()
{
	int A[] = {1, 3, 5, 7, 6, 2, 4};
	const int len = sizeof(A) / sizeof(A[0]);

	std::cout << isNatureSeq(A, len);
	return 0;
}
