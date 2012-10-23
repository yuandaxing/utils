#include <iostream>
#include <limits.h>
using namespace std;
int bruteForce(int board[], int size, int k)
{
	int cur = 0;
	int min = 0;
	int sum = 0;

	if(k <= 0 || size == 0)
		return 0;
	if(k == 1){
		for(int i = 0; i < size; i++)
			sum += board[i];
		return sum;
	}

	cur = bruteForce(board, size, k - 1);
	min = cur;

	for(int i = size - 1; i >= 0; i--){
		sum += board[i];
		cur = max(sum, bruteForce(board, i, k - 1));
		if(cur < min)
			min = cur;
	}
	return min;
}

/*
   f[n][k] = min{max{f[i][k - 1], a[i+1]+...+a[n]} i = 0 to n }
   f[1][k] = a[1];
   f[0][j] = 0 
   f[n][1] = a[1] + a[2]+...+a[n]
 */
#define N	40
int f[N][N];
int sum[N];
void preProcess(int board[], int size)
{
	if(size < 1)
		return ;
	sum[0] = board[0];
	for(int i = 1; i < size; i++)
		sum[i] = board[i] + sum[i - 1];
}

int DP(int board[], int size, int k)
{
	preProcess(board, size);

	for(int i = 1; i <= k; i++){
		for(int j = 0; j < size; j++){
			if(i == 1){
				f[j][i] = sum[j];
				continue;
			}
			int min = sum[j], cur = sum[j];
			for(int p = 0; p <=j; p++){
				cur = max(f[p][i - 1], sum[j] - sum[p]);
				if(cur < min)
					min = cur;	
			}
			f[j][i] = min;
		}
	}
	return f[size - 1][k];
}


bool couldPartition(int sum[], int k, int max, int n)
{
	int pre = 0;
	if(k < 1)
		return false;
	if(sum[pre] > max)
		return false;

	while(sum[pre+1] <= max)
		pre++;

	int j;
	for(int i = 2; i <= k; i++){
		for(j = pre + 1; j < n; j++){
			if(sum[j] - sum[pre] > max)	
				break;
		}
		pre = j - 1;
	}

	if(pre == n - 1)
		return true;
	return false;
}

/*the precondition we assum is max is no less than max{board[i]} */
bool couldPartition2(int board[], int size, int k, int max)
{
	int sum = 0;
	int partition = 0;
	for(int i = 0; i < size; i++){
		sum += board[i];
		if(sum > max){
			sum = board[i];
			partition++;
		}
	}
	partition++;
	return partition <= k;
}

int binSearch(int board[], int size, int k)
{
	preProcess(board, size);

	int left = sum[size - 1] / k;
	int right = sum[size - 1];
	int mid = 0;

	while(left <= right){

			mid = (left + right) / 2;
			if(couldPartition2(board, size, k, mid)){
				right = mid - 1;
			}else{
				left = mid + 1;
			}
	}
	return left;
}

int main()
{
	int board[] = {
		100, 200, 300, 400, 500, 600, 700, 800, 900
	};
	int len =  sizeof(board) / sizeof(board[0]);
	cout<<bruteForce(board, len, 3)<<endl;
	cout<<DP(board, len, 3)<<endl;
	cout<<binSearch(board, len, 3);

	return 0;

}
