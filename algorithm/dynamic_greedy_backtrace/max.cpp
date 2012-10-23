#include <iostream>
#include <utility>
#include <climits>
#include <vector>

std::pair<int, int> findSubMax(int A[], int len, int &max)
{
	std::pair<int, int> ret;
	int start;
	int maxt = INT_MIN;
	int cur = 0;

	for(int i = 0; i < len; i++){
		if(cur > 0)
			cur += A[i];
		else{
			start = i;
			cur = A[i];
		}

		if(cur > maxt){
			maxt = cur;
			ret.first = start;
			ret.second = i;
		}
	}

	max = maxt;
	return ret;
}

const int  LEN = 20 ;
int sums[LEN][LEN];
int tmp[LEN];
int maxSubMaxtri(int m[][5], int r, int c, 
		std::vector<std::pair<int, int> > &vp)
{
	int max = INT_MIN;
	std::pair<int, int> lr, td;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			if(i > 0)
				sums[i][j] = m[i][j] + sums[i - 1][j];
			else
				sums[i][j] = m[i][j];
		}
	}

	for(int i = 0; i < r; i++){
		for(int j = i; j < r; j++){
			for(int k = 0; k < c; k++)
				if(i > 0)
					tmp[k] = sums[j][k] - sums[i - 1][k];
				else 
					tmp[k] = sums[j][k];

			int maxt = 0;
			
			std::pair<int, int> cr = findSubMax(tmp, c, maxt);
			if(maxt > max){
				td.first = i;
				td.second = j;
				lr = cr;
				max = maxt;
			}
		}
	}
	vp.push_back(lr);
	vp.push_back(td);
	return max;
}



int main()
{
	int A[] = {
		4, -9, 3, 5, -7, 10, 13, -20, -8, 7, 9
	};
	const int len = sizeof(A) / sizeof(A[0]);
	int max;
	std::pair<int, int> p = findSubMax(A, len, max);
	std::cout<<"max:"<<max<<"pair:"<<p.first<<" "<<p.second<<std::endl;

	std::vector<std::pair<int, int> > vp;
	int B[4][5] = {
		{
			1, -2, 3, -7,9
		},
		{
			-4, 3, 6, 7, 2
		},{
			3, -6, 2, 4, 5
		}, {
			-8, 9, -5, -1, 2
		}
	};
	int maxt = maxSubMaxtri(B, 4, 5, vp);
	std::cout<<"maxt:"<<maxt<<" bord:"<<vp[0].first
		<<" "<<vp[0].second<<"\t"<<vp[1].first
		<<" "<<vp[1].second;
	return 0;
}
