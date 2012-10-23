#include <iostream>
#include <queue>
#include <utility>
#include <assert.h>
using namespace std;
typedef pair<int, int> Pair;
void maxSlidingWindow(int A[], int n, int w, int B[])
{
	assert(w <= n);
	priority_queue<Pair> queue;

	for(int i = 0; i < w; i++){
		queue.push(Pair(A[i], i));
	}

	B[0] = queue.top().first;

	for(int i = w; i < n; i++){

		queue.push(Pair(A[i], i));

		Pair p = queue.top();
		while(i - w + 1 > p.second){
			queue.pop();
			p = queue.top();
		}

		B[i - w + 1] = p.first;
	}

}

void maxSlidingWindow2(int A[], int len, int w, int B[])
{
	assert(w <= len);

	deque<int> Q;

	for(int i = 0; i < w; i++){
		while (!Q.empty() && A[i] >= A[Q.back()])
			Q.pop_back();
		Q.push_back(i);	
	}
	B[0] = A[Q.front()];

	for(int i = w; i < len; i++){
		while(!Q.empty() && A[i] > A[Q.back()])
			Q.pop_back();
		Q.push_back(i);
		while(!Q.empty() && Q.front() < i - w + 1)
			Q.pop_front();

		B[i - w + 1] = A[Q.front()];
	}
}

void printArray(int B[], int len)
{
	for(int i = 0; i < len; i++){
		cout<<B[i]<<"\t";	
	}

	cout<<endl;
}

int main()
{
	int A[] = {1, 3, -1, -3, 5, 3 , 6, 7 };
	int B[10] = {0};
	int len = sizeof(A) / sizeof(A[0]);
	maxSlidingWindow(A, len, 3, B);
	printArray(B, len - 3 + 1);
	maxSlidingWindow2(A, len, 3, B);
	printArray(B, len - 3 + 1);
	return 0;
}
