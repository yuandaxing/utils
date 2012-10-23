#include <iostream>
#include <vector>
#include <set>
class NumGen {
	private:
		std::vector<int> vi_;
		std::vector<bool> vb_;
	public:
		NumGen( int *s, int *e ) :
			vi_(s, e) {
				vb_.assign(vi_.size(), false); 
			}
		NumGen( std::vector<int> &v ):
			vi_(v) {
				vb_.assign(vi_.size(), false);
			}
		void gen(std::set<int> &set, int i) ;
};

void NumGen::gen(std::set<int> &set, int i) {
	if(static_cast<unsigned>(i) == vi_.size()){
		int sum = 0;
		bool one = false;
		for(int j = 0; static_cast<unsigned>(j) < vi_.size(); j++) {
			if(vb_[j]) {
				sum += vi_[j];
				one = true;
			}
		}
		if(one)
			set.insert(sum);
		return ;
	}
	vb_[i] = true;
	gen(set, i+1);
	vb_[i] = false;
	gen(set, i+1);
}
std::ostream& operator<<(std::ostream &os, const std::set<int> &set) {
	for(std::set<int>::iterator iter = set.begin(); iter != set.end(); iter++) {
		os << *iter << " ";
	}
	return os;         
}
int main() {
	int a[] = { 1, 2, 4, 8, 16, 32, 64};
	const int len = sizeof(a) / sizeof(a[0]);
	NumGen ng(a, a+len);
	std::set<int> set;
	ng.gen(set, 0);
	std::cout << set << std::endl;
	return 0;
}
