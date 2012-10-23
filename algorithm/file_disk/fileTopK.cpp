/*
 * =====================================================================================
 *
 *       Filename:  fileTopK.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年07月06日 19时33分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <queue>
#include <stdio.h>
#include <string>
#include <stdio.h>
#include <vector>
template <typename T>
class Compare {
	public:
		bool operator() (const T & lhs, const T &rhs) {
			return lhs > rhs ;
		}
};
bool more(unsigned int lhs, unsigned int rhs) {
	return lhs > rhs ;
}
template <typename T>
class TopKQueue {
	public:
		TopKQueue(const int size) :
			size_(size), q_() { }
		void add(const T &ele) {
			if(q_.size() >= static_cast<unsigned>(size_) ) {

				if(q_.top() < ele) {
					q_.pop();
					q_.push(ele);
				}
			} else {
				q_.push(ele) ;
			}	
		}

		const T& top() const {
			return q_.top();
		}
		void pop() {
			q_.pop();
		}

		bool isEmpty() {
			return q_.empty();
		}
	private:
		const int size_;
		std::priority_queue<T, std::vector<T>, Compare<T> > q_;
};	
int main ( int argc, char *argv[] )
{
	const int nbuff = 1024 * 512;
	std::string str = "testfile.txt";
	FILE *in = fopen(str.c_str(), "r");
	if ( in == NULL ) {
		fprintf(stderr, "cannot open read file");
	}
	char *buff = new char [nbuff];
	setbuffer(in, buff, nbuff);
	
	TopKQueue<unsigned> tkq(10);
	unsigned int cur = 0;
	while( fscanf(in, "%u", &cur) > 0 ) {
		tkq.add(cur);
	}

	delete[] buff;
	fclose(in);

	while( !tkq.isEmpty() ) {
		fprintf(stderr, "%u ", tkq.top() );
		tkq.pop();
	}

	fprintf(stderr, "\n");

	return 0;
}				/* ----------  end of function main  ---------- */
