/*
 * =====================================================================================
 *
 *       Filename:  Trie.cpp
 *
 *    Description:  we implement five interface, addWord(const String &)
 *                 	countPrefix(const String& pre) countWord(const String& w), 
 *    				hasWord(const String&)
 *    				sorting(const Trie &t) 
 *
 *        Version:  1.0
 *        Created:  2012年09月11日 21时30分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Random.h"
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include "../../Common.h"
inline int charToIndex(char c) {
	return c - 'a';
}

struct node {
	node( ): nPrefix_(0), nWord_(0) {
		memset(ptr_, 0, sizeof(ptr_));
	}
	~node() {
		for( int i = 0 ; i < NMaxChar ; i++ )
		{
			delete ptr_[i];
		}
	}

	static const int NMaxChar = 26;
	node *ptr_[NMaxChar];
	int nPrefix_, nWord_;
};
const int node::NMaxChar;

class Trie {
	public:
		Trie(): root(new node()){ }
		~Trie() {
			delete root;
		}

		void addWord(const std::string &w);
		int countPrefix(const std::string &p);
		int countWord(const std::string &w);
		bool hasWord(const std::string &w);
		void printSortingString();

	private:
		//no copy allowed
		Trie(const Trie&);
		Trie& operator=(const Trie&);

		int countHelper(const std::string &s, bool prefix = true) {
			node *n = root;
			for( int i = 0 ; static_cast<unsigned>(i) < s.size() && 
					n != NULL ; i++ )
			{
				n = n->ptr_[charToIndex(s[i])];
			}
			if(n == NULL)
				return 0;
			if(prefix)
				return n->nPrefix_;
			else
				return n->nWord_;
		}

		void printHelper(node *cur, std::vector<char>& vc) {
			if(cur == NULL)
				return ;

			if(cur->nWord_ > 0)
				std::cout << vc << "\t";

			for( int i = 0 ; i < node::NMaxChar ; i++ )
			{
				if( cur->ptr_[i] != NULL )
				{
					vc.push_back(static_cast<char>(i+'a'));
					printHelper(cur->ptr_[i], vc);
					vc.pop_back();
				}
			}
		}

		//data 
		node *root;
};
void Trie::addWord(const std::string &w) {
	node *n = root;
	for( int i = 0 ; static_cast<unsigned>(i) < w.size() ;
			i++ )
	{
		int idx = charToIndex(w[i]);
		if( n->ptr_[idx] == NULL )
		{
			n->ptr_[idx] = new node();
		}
		n = n->ptr_[idx];
		if(static_cast<unsigned>(i) == w.size() - 1)
			n->nWord_++;
		else
			n->nPrefix_++;	 
	}	
}
int Trie::countPrefix(const std::string &p) {
	return countHelper(p);
}
int Trie::countWord(const std::string &w) {
	return countHelper(w, false);
}
bool Trie::hasWord(const std::string &w) {
	return countWord(w) > 0;
}
void Trie::printSortingString() {
	std::vector<char> vc;
	printHelper(root, vc);
}
int main(int argc, char *argv[])
{
	const char a[] = "abcdefghijklmnopqrstuvwxyz";
	const int NStrings = 1000;
	const int stringLen = 3;
	Trie trie;
	threadSafe::Random::seed();
	for( int i = 0 ; i < NStrings ; i++ )
	{
		trie.addWord(threadSafe::Random::getRandString(a, 
					stringLen));
	}

	assert(trie.countWord("") == 0 &&
			trie.countPrefix("") == 0);
	const char *ss[] = {"aba", "bc", "cd", "ef"};

	for( int i = 0 ; static_cast<unsigned>(i) < 
			sizeof(ss) / sizeof(const char *) ; i++ )
	{
		std::cout << "Prefix " << ss[i] << ":" 
			<< trie.countPrefix(ss[i]) << std::endl;
		std::cout << "Word " << ss[i] << ":" 
			<< trie.countPrefix(ss[i]) << std::endl;
	}

	trie.printSortingString();
	std::cout << std::endl;
	return 0;
}
