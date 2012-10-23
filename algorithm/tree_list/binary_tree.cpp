/*
 * =====================================================================================
 *
 *       Filename:  binary_tree.cpp
 *
 *    Description:  demonstrate some binary tree algorithm
 *    				enjoy it!!!
 *
 *        Version:  1.0
 *        Created:  2012年08月25日 22时18分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <assert.h>

using namespace std;

typedef struct tNode{
	int data;
	struct tNode *left, *right;
}tNode, *ptNode;



//question 7

bool hasPathSum(ptNode root, int sum)
{
	// to test some special case, empty tree
	if(root == NULL )
		return false;

	sum -= root->data;

	if(root->left == NULL && root->right == NULL) {
		if(sum == 0)
			return true;
		else
			return false;
	}

	if( root->left != NULL && 
			hasPathSum(root->left, sum) )
	{
		return true;
	} 

	if( root->right != NULL && 
			hasPathSum(root->right, sum) )
	{
		return true;
	}

	return false;
}

int main(int argc, char *argv[])
{

	return 0;
}
