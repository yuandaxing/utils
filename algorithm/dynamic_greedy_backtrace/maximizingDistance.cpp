#include <iostream>
#include <stdlib.h>
using namespace std;
int b[] = {
	4, 3, 5, 2, 1, 3, 2, 3
};

int bruteForce()
{
	int len  = sizeof(b) / sizeof(b[0]);
	int max = 0;
	int j = 0;

	for(int i = 0; i < len; i++){
		for(j = len - 1; j > i && b[j] <= b[i]; j--)
			;
		if(j > i && j - i > max){
			max = j - i;
		}
	}

	return max;
}

typedef struct {
	int val;
	int index;
}dataIndex;
dataIndex di[sizeof(b) / sizeof(b[0])];

static int compare(const void *a, const void *b)
{
	const dataIndex *left = (dataIndex *)a;
	const dataIndex *right = (dataIndex *)b;
	int d = left->val - right->val;
	if(d != 0)
		return d;
	return right->index - left->index;
}
int sortingMethod()
{
	int tmp[sizeof(b) / sizeof(b[0])]={
		0
	};
	int len = sizeof(b) / sizeof(b[0]);
	for(int i = 0; i < len; i++){
		di[i].val = b[i];
		di[i].index = i;
	}
	qsort(di, len, sizeof(dataIndex), compare);
	int mdis = len - 1;
	int max = 0;
	for(int i = 0; i < len; i++){
		while(mdis >= 0 && tmp[mdis] == 1) 
			mdis--;
		if(mdis - di[i].index > max)
			max = mdis - di[i].index;
		tmp[di[i].index] = 1;
	}
	return max;
}

int linear()
{
	dataIndex tmp[sizeof(b) / sizeof(b[0])];		

	int len = sizeof(b) / sizeof(b[0]);
	if(len < 1)
		return 0;
	tmp[0].val  = b[0];
	tmp[0].index = 0;
	int last = 0;	
	for(int i = 1; i < len; i++){

		if(b[i] < tmp[last].val){
			tmp[++last].val = b[i];
			tmp[last].index = i;
		}	
	}

	int max = 0;
	for(int j = len - 1; j >= 0; j--){
		if(last >= 0 && b[j] > tmp[last].val){
			while(last - 1 >= 0 && b[j] > tmp[last - 1].val)
				last--;
			if(j - tmp[last].index > max)
				max = j - tmp[last].index;
			last--;
		}
	}
	return max;
}
int main()
{
	cout<<bruteForce()<<endl;
	cout<<sortingMethod()<<endl;
	cout<<linear()<<endl;
	return 0;
}
