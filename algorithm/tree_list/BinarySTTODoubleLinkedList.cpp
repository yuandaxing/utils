#include <iostream>

typedef struct node {
	int data;
	struct node *left, *right;
}node;

/* head & pre must be NULL when you call it */
void treeToList(node *&head, node *& pre, node *cur) {
	if( cur == NULL )
	{
		return ;
	}

	treeToList(head, pre, cur->left);
	node *right = cur->right;

	if( head == NULL )
	{
		head = cur;
		cur->left = cur->right = cur;
	} else {
		pre->right = cur;
		cur->left = pre;
		head->left = cur;
		cur->right = head;
	}

	pre = cur;

	treeToList(head, pre, right);
}
void forward_print(node *h) {
	if(h == NULL)
		return ;

	node *cur = h;
	std::cout << cur->data << "\t";
	cur = cur->right;
	while(cur != h) {
		std::cout << cur->data << "\t";
		cur = cur->right;
	}
	std::cout << std::endl;
}
void backward_print(node *h) {
	if(h == NULL)
		return ;

	node *tail = h->left, *cur = tail;
	std::cout << cur->data << "\t";
	cur = cur->left;
	while(cur != tail) {
		std::cout << cur->data << "\t";
		cur = cur->left;
	}
	std::cout << std::endl;
}

/* return the depth */
int maxDistance(node *n, int &maxD) {
	if( n == NULL )
	{
		maxD = 0;
		return 0;
	}
	int l_depth, r_depth, l_maxD, r_maxD;
	l_depth = maxDistance(n->left, l_maxD);
	r_depth = maxDistance(n->right, r_maxD);

	int max = std::max(l_maxD, r_maxD);
	maxD = std::max(l_depth + r_depth, max);
	return std::max(l_depth, r_depth) + 1;
}
int main(int argc, char *argv[])
{
	node n1 = {10, NULL, NULL};
	node n2 = {19, NULL, NULL};
	node n3 = {18, &n1, &n2};
	node n4 = {25, NULL, NULL};
	node n5 = {30, &n4, NULL};
	node n6 = {20, &n3, &n5};

	node *h = NULL, *pre = NULL;
////	treeToList(h, pre, &n6);
//	foward_print(h);
//	backward_print(h);
//	return 0;
	int max;
	maxDistance(&n5, max);
	std::cout << max << std::endl;	
}



