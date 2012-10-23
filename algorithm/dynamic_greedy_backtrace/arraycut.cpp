/*
 * =====================================================================================
 *
 *       Filename:  arraycut.cpp
 *    Description:  cut array into m part, each part has the same sum, make the sum biggest
 *        Version:  1.0
 *        Created:  2012年08月09日 10时38分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
void discompositionNum(int num, std::vector<int> &vi) {
	int i = 0;
	for ( i = num; i >= 2 ; i-- ) {
		int k = num / i ;
		if(k * i == num) {
			vi.push_back(k);
		}
	}
}

class equal_false {
	public:
		bool operator() (const bool & T) {
			return T == false;
		}
};
int get_next_false_index(std::vector<bool> &used, int start) {
	while(static_cast<unsigned>(start) < used.size() 
			&& used[start] == true)
		start++;
	return start;
}

bool discom_helper(std::vector<int> &array, int k, 
		std::vector<bool> &used, int start, int left, bool first) {

	if(left == 0) {
		std::vector<bool>::iterator iter = std::find_if(used.begin(), 
				used.end(), equal_false());
		if(iter == used.end())
			return true;
		int idx = iter - used.begin();
		return discom_helper(array, k, used, idx, k, true);
	}

	if(static_cast<unsigned>(start) >= used.size()) {
		return false;
	}
	used[start] = true;
	left -= array[start];
	int next = get_next_false_index(used, start + 1);
	bool res = discom_helper(array, k, used, next, left, false);
	
	//if we succeed
	if(res) return true;

	//if we failed, we will try other cases
	used[start] = false;
	left += array[start];
	if(first && !res) {
		return false;
	} else {
		while(static_cast<unsigned>(next) < array.size()) { 
			if(discom_helper(array, k, used, next, left, false))
				return true;
			next = get_next_false_index(used, next + 1);
		}
		return false;
	}
}



bool couldDiscomToK(std::vector<int> &array, int K) {
	std::vector<bool> used(array.size(), false);
	return discom_helper(array, K, used, 0, K, true);
}
bool findMaxSubarrySum(std::vector<int> &array, int &max_sum) {
	std::sort(array.begin(), array.end());
	
	int sum = std::accumulate(array.begin(), array.end(), 0);
	std::vector<int> sums;
	discompositionNum(sum, sums);
	std::vector<int>::iterator iter  = std::find_if(sums.begin(), sums.end(), 
			std::not1(std::bind2nd(std::less<int>(), array[array.size() - 1])));
	std::cout << *iter << std::endl;

	bool find = false;
	while(iter !=  sums.end()) {
		if(couldDiscomToK(array, *iter)) {
			find = true;
			max_sum = *iter;
		}
		iter++;
	}
	return find;
}
int main ( int argc, char *argv[] )
{
	int a[] = {3, 2, 4, 3, 6};
	std::vector<int> vi(a, a + 5);
	int max_sum;
	if(findMaxSubarrySum(vi, max_sum)) {
		std::cout << "max_sum:" << max_sum << std::endl;
	}
	int a1[] = {1, 2, 4, 3, 3, 1};
	std::vector<int> vi1(a1, a1 + 6);
	int max_sum1;
	if(findMaxSubarrySum(vi1, max_sum1)) {
		std::cout << "max_sum1:" << max_sum1 << std::endl;
	}
	return 0;
}				/* ----------  end of function main  ---------- */
