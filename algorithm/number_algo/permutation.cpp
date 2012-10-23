#include <sstream>
#include "../../Common.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;
void allSubSet( vector<vector<int> > &all, 
     const vector<int> &set, int start )
{
     if( set.size() == static_cast<unsigned>(start) ){
                   vector<int> empty;
                   all.push_back( empty );
     }else{
           int ele = set[start];
           allSubSet( all, set, start+1 );
           int size = all.size();
           for( int i = 0; i < size; i++ ){
                   vector<int> sub = all[i];
                   sub.push_back(ele);
                   all.push_back(sub);
           }      
     }
}

class Permutation {
	private:
		std::vector<int> vi_;
		int count_;
	public:
		Permutation(int *s, int *e) :
			vi_(s, e), count_(0) { }
		void gen(int s) {
			if(static_cast<unsigned>(s) >= vi_.size()) {
				std::cout << vi_ ;
				count_++;
			}
			for( int i = s ; static_cast<unsigned>(i) < vi_.size() ; i++ )
			{
				std::swap(vi_[s], vi_[i]);
				gen(s+1);
				std::swap(vi_[s], vi_[i]);
			}
		}
		int count() {
			return count_;
		}
};


//perfect Permutation Hashing
std::vector<int> factorials;
void initFactor(int n) {
	factorials.assign(n, 0);
	factorials[0] = 1;
	for( int i = 1 ; i < n ; i++ )
	{
		factorials[i] = i * factorials[i-1];
	}
}
template <typename T>
size_t PermutationToNumber(const T permutation[], int n) {
	size_t result = 0;
	for (int j = 1; j < n; ++j) {
		int count = 0;
		for (int k = 0; k < j; ++k) {
			if (permutation[k] > permutation[j])
				++count;
		}
		result += count * factorials[j];
	}
	return result;
}
int main()
{
    vector<vector<int> > all;
    int a[] = {1, 2, 3};
    vector<int> set;
    for(int i = 0; static_cast<unsigned>(i) < sizeof(a) / sizeof(int); i++){
            set.push_back(a[i]);
    }
    allSubSet(all,set, 0); 

	std::cout << all << std::endl;

	int b[] = {1,2,3,4,5};
	const int len = sizeof(b) / sizeof(b[0]);
	Permutation per(b, b+len);
	per.gen(0);
	std::cout << per.count() << std::endl;


	//int c[] = {2, 1, 3, 4, 5};
	int c[] = {5, 4, 3, 2, 1};
	const int lenc = sizeof(c) / sizeof(c[0]);
	initFactor(lenc);
	std::cout << factorials << std::endl;
	std::cout << PermutationToNumber(c, lenc) << std::endl;
    return 0;
}
