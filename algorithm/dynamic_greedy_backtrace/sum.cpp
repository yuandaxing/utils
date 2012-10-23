#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;
int cmp(const void  *a, const void *b)
{
	return *(const int *)a - *(const int *)b;
}
vector< vector<int> > sum2(int A[], int start, int end, int K)
{
	vector< vector<int> > ret;
	for(int i = 0,  j = end; i < j; ){
		int sum = A[i] + A[j];
		if(sum > K)
			j--;
		else if(sum < K)
			i++;
		else{
			vector<int> tmp;
			tmp.push_back(A[i]);
			tmp.push_back(A[j]);
			ret.push_back(tmp);
			j--, i++;
		}
	}
	return ret;
		
}

vector< vector<int> > sum3(int A[], int len, int K)
{
	vector< vector<int> > ret;
	for(int i = 0; i < len; i++){
		if(A[i]*3 > K) break;
		vector<vector<int> > tmp = sum2(A, i+1, 
				len - 1, K - A[i]);

		for(unsigned int j = 0; j < tmp.size(); j++){
			vector<int> cur;
			cur.push_back(A[i]);
			cur.push_back(tmp[j][0]);
			cur.push_back(tmp[j][1]);
			ret.push_back(cur);
		}
	}
	return ret;
}


void resolve(int A[], int sum, vector<int> & cur,
		int pos, vector<vector<int> > &res, int len, int K)
{
	if(pos >= len){
		if(sum == K){
			vector<int> tmp = cur;
			res.push_back(tmp);
		}
		return ;
	}
	resolve(A, sum, cur, pos + 1,
		  res, len, K );

	cur.push_back(A[pos]);
	sum += A[pos];
	resolve(A, sum, cur, pos + 1, 
			res, len, K);

	cur.pop_back();
}

void printSum(vector< vector<int> >  v )
{
	for(unsigned int i = 0; i < v.size(); i++){
		for(unsigned int j = 0; j < v[i].size(); j++)
			cout<<"\t"<<v[i][j];
		cout<<endl;
	}
}

int main()
{
	int A[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, -1, -2, -3, -4, -5
	};

	const int len = sizeof(A) / sizeof(A[0]);
	qsort(A, len, sizeof(A[0]), cmp);

	printSum(sum2(A, 0, len - 1, 10));

	printSum(sum3(A, len, 10));
	cout<<endl<<endl;


	int B[] = {
		0, 9, 7, -10, 3, 1, 2
	};
	const int lenB = sizeof(B) / sizeof(B[0]);
	vector<vector<int> > res;
	vector<int> tmp;

	resolve(B, 0, tmp, 0, res, lenB, 10);
	printSum(res);
	
	return 0;
}
