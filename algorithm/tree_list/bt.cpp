
#include <iostream>
#include <vector>
#include <assert.h>
#include <limits.h>
using namespace std;

typedef struct node{
	int data;
	struct node *left, *right;
	node(int n, struct node *l = NULL, 
			struct node *r = NULL) : data(n), left(l), right(r) { }
}node;

std::ostream& operator<<(std::ostream& out, 
		const std::vector<node *>& vnp) {
	for( int i = 0 ; static_cast<unsigned>(i) < vnp.size() ; i++ )
	{
		out << vnp[i]->data << " ";
	}
	out << std::endl;
	return out;
}

void printPaths_helper(struct node * n, vector<node *> &vn);

void printPaths(struct node* node) {
	std::vector<struct node* > vn;
	printPaths_helper(node, vn);
}

void printPaths_helper(struct node * n, vector<node *> &vn) {
	if(n == NULL)
		return ;
	vn.push_back(n);
	if(n->left == NULL && n->right == NULL)
		std::cout << vn << std::endl;

	if(n->left != NULL)
		printPaths_helper(n->left, vn);
	if(n->right != NULL)
		printPaths_helper(n->right, vn);
	vn.pop_back();
}

void mirror(struct node *n) {
	if(n == NULL) return ;

	mirror(n->left);
	mirror(n->right);
	std::swap(n->left, n->right);
}
//ps 10
struct node * duplicate(struct node *n) {
	assert(n != NULL);
	return new node(n->data);

}
struct node * dupTree(struct node *n) {
	if(n == NULL)
		return NULL;
	
	struct node *nn = duplicate(n);
	nn->left = dupTree(n->left);
	nn->right = dupTree(n->right);
	return nn;
}

//ps 11
int sameTree(struct node *a, struct node *b) {
	if(a == NULL && b == NULL)
		return true;

	if(a == NULL || b == NULL)
		return false;

	if(a->data != b->data)
		return false;
	if(sameTree(a->left, b->left) && sameTree(a->right, b->right) )
		return true;
	return false;
}
//ps 12
//actually the problem is a Catalan.
// P(n) = P(0) * P(n - 1) + P(1) * P(n - 2) + P(2) * P(n - 3)
// 	 + ..... + P(n - 2) * P(1) + P(n - 1) * P(0) = C(2*n, n) / n+1;
// while n is 4, the result is 8*7*6*5 / 4*3*2*1 / 5 = 14;
// dynamic programming can apply this problem.
//P(1) = 1, P(0) = 1;
//
const int N = 10000;
int B[N] = {1};
int countTrees(int numKeys) {
	if(B[numKeys] != 0)
		return B[numKeys];
	
	for(int i = 0; i <= numKeys - 1; i++) {
		B[numKeys] += countTrees(i) * countTrees(numKeys - i - 1);
	}
	return B[numKeys];
}

//ps 13
int maxValue(node *n) {
	assert(n != NULL);
	int max = n->data;
	if(n->left)
		max = std::max(max, maxValue(n->left));
	if(n->right)
		max = std::max(max, maxValue(n->right));
	return max;
}
int minValue(node *n) {
	assert(n != NULL);
	int min = n->data;
	if(n->left)
		min = std::min(min, minValue(n->left));
	if(n->right)
		min = std::min(min, minValue(n->right));
	return min;
}
int isBST(struct node *n) {
	if(n == NULL)
		return true;
	int child = isBST(n->left) && isBST(n->right);

	if(child == false)
		return false;

	int maxleft = INT_MIN;
	int minright = INT_MAX;
	if(n->left != NULL)
		maxleft = maxValue(n->left);
	if(n->right != NULL)
		minright = minValue(n->right);
	return n->data >= maxleft && n->data <= minright;
}

//ps 14
/* 
 Returns true if the given tree is a binary search tree 
 (efficient version). 
*/ 

int isBSTRecur(struct node* node, int min, int max) ;

int isBST2(struct node* node) { 
  return(isBSTRecur(node, INT_MIN, INT_MAX)); 
}

/* 
 Returns true if the given tree is a BST and its 
 values are >= min and <= max. 
*/ 
int isBSTRecur(struct node* node, int min, int max) { 
	if(node == NULL)
		return true;
	if(!(node->data >= min && node->data <= max))
		return false;

	return isBSTRecur(node->left, min, node->data) &&
		isBSTRecur(node->right, node->data, max);
}

int main(int argc, char *argv[])
{

	node n8(4), /* n4(1, NULL, &n8), */ n4(1, &n8), 
		 n5(6), n6(19), n7(21), n2(5, &n4, &n5),
		 n3(20, &n6, &n7), n1(10, &n2, &n3);
	
	printPaths(&n1);
	
	//mirror(&n1);
	//std::cout << "test after mirror" << std::endl;
	//printPaths(&n1);
	

	node *n = dupTree(&n1);
	std::cout << "print duplicate tree" << std::endl;
	printPaths(n);

	std::cout << "test same tree\n";
    std::cout << "sameTree(&n1, n):" <<  sameTree(&n1, n) << std::endl;
	std::cout << "sameTree(n, &n2):" <<  sameTree(n, &n2) << std::endl;

	std::cout << "countTrees(1):"<< countTrees(1) << std::endl;
	std::cout << "countTrees(2):"<< countTrees(2) << std::endl;
	std::cout << "countTrees(10):"<< countTrees(10) << std::endl;
	std::cout << "countTrees(5):"<< countTrees(5) << std::endl;

	std::cout << "isBST(&n1):" << isBST(&n1) << std::endl;
	std::cout << "isBST(&n1):" << isBST(n) << std::endl;
	std::cout << "isBST2(&n1):" << isBST2(n) << std::endl;

	return 0;
}
