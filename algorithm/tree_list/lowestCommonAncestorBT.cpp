#include <iostream>
#include <assert.h>

using namespace std;

typedef struct tNode{
	int data;
	struct tNode *left, *right;
}tNode, *ptNode;

typedef struct {
	int data;
	int left, right;
}tree;

typedef ptNode list;

void buildTree(ptNode *p, int index, tree T[])
{
	assert(p != NULL);

	if(index == -1){
		*p = NULL;
		return ;
	}

	ptNode node = new tNode();
	node->data = T[index].data;
	*p = node;
	buildTree(&node->left, T[index].left, T);
	buildTree(&node->right, T[index].right, T);
}

void preOrder(ptNode root){
	if(root == NULL)
		return ;
	cout<<root->data<<"\t";
	preOrder(root->left);
	preOrder(root->right);
}

ptNode preOrderFind(ptNode root, int key)
{
	ptNode node;

	if(root == NULL)
		return NULL;

	if(root->data == key)
		return root;

	if((node = preOrderFind(root->left, key))
		   	!= NULL)
		return node;

	if((node = preOrderFind(root->right, key))
			!= NULL)
		return node;

	return NULL;
}
ptNode findLowestParent(ptNode root, ptNode p1, ptNode p2)
{
	assert(p1 != NULL && p2 != NULL);

	if(root == NULL)
		return NULL;

	ptNode left = findLowestParent(root->left, p1, p2);
	ptNode right = findLowestParent(root->right, p1, p2);

	if((left != NULL && right != NULL) || root == p1 || root == p2)
		return root;
	if(left)
		return left;
	if(right)
		return right;

	return NULL;
}
int countMatches(ptNode root, ptNode p1, ptNode p2)
{
	if(root == NULL)
		return 0;
	int count = 0;
	if(root == p1 || root == p2)
		count++;
	return count + countMatches(root->left, p1, p2) + countMatches(root->right, p1, p2);
}

ptNode findLowestParent2(ptNode root, ptNode p1, ptNode p2)
{
	if(root == NULL)
		return NULL;

	bool rootMatch = false;
	int left = 0;
	int right = 0;

	if(root == p1 || root == p2)
		rootMatch = true;
	left = countMatches(root->left, p1, p2);
	right = countMatches(root->right, p1, p2);
	
	if(rootMatch && left + right > 0)
		return root;

	if(left == 1 && right == 1)
		return root;
	
	if(left == 2)
		return findLowestParent2(root->left, p1, p2);

	if(right == 2)
		return findLowestParent2(root->right, p1, p2);	

	return NULL;
}
//construct a tree from the array a which is the preorder 
	//visit seq and b which is inorder vist seq
void constructFromPreInOrder(ptNode *root, int a[], 
		int b[], int ia, int ja, int ib, int jb)
{
	assert(root != NULL);
	if(ia > ja){
		*root = NULL;
		return ;
	}
	int i;
	for(i = ib; i <= jb; i++){
		if(a[ia] == b[i])
			break;
	}

	assert(i >= ib && i <= jb);
	*root = new tNode();
	(*root)->data = a[ia];
	constructFromPreInOrder(&(*root)->left, a, b, ia + 1, i - ib + ia, ib, i - 1);
	constructFromPreInOrder(&(*root)->right, a, b, i - ib + ia + 1, ja, i + 1, jb);
}

void  BSTToDLL(ptNode &pre, ptNode root, ptNode &head)
{
	if(root == NULL)
		return ;
	if(root->left != NULL)
		BSTToDLL(pre, root->left, head);

	if(pre == NULL){ //we donnot require it is a double circular list
		head = root;
	}else{
		pre->right = root;
		root->left = pre;
	}
	//the last pre is here
	pre = root;

	if(root->right)
		BSTToDLL(pre, root->right, head);

}

void listVisit(ptNode head)
{

	ptNode n = head;
	if(n == NULL)
		return ;
	n = head;
	while(n != NULL){
		cout<<n->data<<"\t";
		n = n->right;
	}
	cout<<endl;

}
ptNode convertBST(int array[], int left, int right)
{
	if(left > right || array == NULL)
		return NULL;

	int mid = (right + left) / 2;

	ptNode n = new tNode();
	n->data = array[mid];
	n->left = convertBST(array, left, mid - 1);
	n->right = convertBST(array, mid + 1, right);

	return n;
}

ptNode convertListToTree(list &head, int start, int end)
{
	if(start > end)
		return NULL;

	int mid = (start + end) / 2;
	ptNode left = convertListToTree(head, start, mid -1);
	ptNode root = new tNode();
	root->data = head->data;
	root->left = left;

	head = head->right;
	root->right=convertListToTree(head, mid + 1, end);
	return root;

}
int main()
{
	tree  mytree[] = {
		{
			3, 1, 6
		},{
			5, 2, 3
		},{
			6, -1, -1
		},{
			2, 4, 5
		},{
			7, -1, -1
		},{
			4, -1, -1
		},{
			1, 7, 8
		},{
			0, -1, -1
		},{
			8, -1, -1
		}
	};
	int pre[] = {7,10,4,3,1,2,8,11};
	int in[] = {4,10,3,1,7,11,8,2};
	ptNode root;
	buildTree(&root, 0, mytree);
	preOrder(root);
	cout<<endl;
	ptNode left =  preOrderFind(root, 5);
	ptNode right = preOrderFind(root, 6);
	cout<<"the lowes is :"<<findLowestParent(root, left, right)->data
		<<endl;
	cout<<"the lowes is :"<<findLowestParent2(root, left, right)->data
		<<endl;
	cout<<endl;


	int len = sizeof(pre) / sizeof(pre[0]);

	ptNode root2 = NULL;
	constructFromPreInOrder(&root2, pre, in, 0, len - 1, 0, len - 1);
	preOrder(root2);
	cout<<endl;
	ptNode prep = NULL;
	ptNode head = NULL;
	BSTToDLL(prep, root2, head);
	listVisit(head);
	ptNode root4 = convertListToTree(head, 0, len - 1);
	preOrder(root4);
	cout<<endl;
	ptNode root3 = convertBST(pre, 0, len - 1);
	preOrder(root3);
	cout<<endl;
	return 0;
}
