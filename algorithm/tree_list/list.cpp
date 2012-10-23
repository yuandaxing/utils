#include <stdlib.h>
#include "common_head.h"
#include <stack>
#include <utility>

list *reverse_nore(list *head){
	if(head == NULL || head->next == NULL)
		return head;

	list *pre = head, *cur = head->next;

	while(cur != NULL){
		pre = cur;
		cur = cur->next;
	}
	cur = head;
	head = pre;

	list *next = NULL;
	while(cur != head){
		next = cur->next;
		cur->next = head->next;
		head->next = cur;
		cur = next;
	}
	return head;
}

list *insert_tail(list *n, list *h)
{
	list *pre = NULL, *cur = NULL;
	if(h == NULL)
		return n;
	pre = h;
	cur = h->next;
	while(cur != NULL){
		pre = cur;
		cur = cur->next;
	}

	n->next = NULL;
	pre->next = n;

	return h;
}

list * reverse_re1(list *h)
{
	if(h == NULL || h->next == NULL)
		return h;

	list *head = reverse_re1(h->next);
	head = insert_tail(h, head);
	return head;
}

list * reverse_re2(list *h)
{
	if(h == NULL || h->next == NULL)
		return h;

	list *next = h->next; //next is not null
	list *f = h;

	h = reverse_re2(h->next);

	f->next = NULL;
	next->next = f;
	return h;
}
int listlen(list *h)
{
	int sum = 0;
	while(h != NULL){
		sum++;
		h = h->next;
	}
	return sum;
}

tnode *ltot_helper(list * &h, int n)
{
	if(n <= 0)
		return NULL;
	int left = n / 2;
	
	tnode *leftn = ltot_helper(h, left);
	tnode *node = new tnode();
	node->data = h->data;
	node->left = leftn;
	h = h->next;
	tnode *right = ltot_helper(h, n - 1 - left);
	node->right = right;
	return node;
}

tnode * list_to_tree(list *h)
{

	int n = listlen(h);
	return ltot_helper(h, n);
}

tnode * array_to_tree(int A[], int len)
{
	if(len <= 0 || A == NULL)
		return NULL;

	int left = len / 2;
	tnode *n = new tnode();
	if(n == NULL){
		cout<<"oom\n";
		exit(0);
	}

	n->data = A[left];
	n->left = array_to_tree(A, left);
	n->right = array_to_tree(A + left + 1, len - left - 1);
	return n;
}

void tree_to_list(tnode *&pre, tnode *root)
{
	if(root == NULL)
		return ;
	tree_to_list(pre, root->left);
	if(pre != NULL){
		pre->right = root;
	}
	root->left = pre;
	pre = root;
	tree_to_list(pre, root->right);
}

tnode *treeto_list(tnode *root)
{
	tnode *pre = NULL;
	tnode *next = NULL;

	tree_to_list(pre, root);
	while(root != NULL){
		next = root;
		root = root->left;
	}
	return next;
}

tnode *tree_to_list(tnode *root)
{
	if(root == NULL)
		return root;

	stack<tnode *> s;
	tnode *pre = NULL;
	tnode *save = root;
	while(root != NULL){
		s.push(root);
		root = root->left;
	}
	while(!s.empty()){
		tnode *cur = s.top();
		s.pop();
		if(pre){
			pre->right = cur;
		}
		cur->left = pre;
		pre = cur;
		cur = cur->right;
		while(cur){
			s.push(cur);
			cur = cur->left;
		}
	}

	while(save->left != NULL){
		save = save->left;
	}
	return save;
}

tnode *tree_to_list2(tnode *root)
{
	if(root == NULL)
		return root;

	typedef pair<bool, tnode *> entry;
	stack<entry> s;

	tnode *cur = root, *pre = NULL;
	tnode *head = NULL;

	s.push( entry(false, cur) );

	while(!s.empty()){
		entry & en = s.top();
		cur = en.second;
		if(en.first == false){
			en.first = true;
			if(cur->left != NULL)
				s.push(entry(false, cur->left));
		}else{
			s.pop();
			if(pre)
				pre->right = cur;
			cur->left = pre;
			pre = cur;
			if(head == NULL)
				head = cur;
			if(cur->right)
				s.push(entry(false, cur->right));
		}
	}
	return head;
}

void travel_dlist(tnode *h)
{
	while(h != NULL){
		cout<<h->data<<"   ";
		h = h->right;
	}
	cout<<endl;
}

int main()
{
	int A[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10 	
	};

	list *head = NULL;
	const int len = sizeof(A) / sizeof(A[0]);
	head = construct(A, len);
	travel(head);
	head = reverse_nore(head);
	travel(head);
	head = reverse_re1(head);
	travel(head);
	head = reverse_re2(head);
	travel(head);

	in_travel(list_to_tree(head));
	cout<<endl;
	tnode *root = array_to_tree(A, len);
	in_travel(root);
	cout<<endl;
	//tnode *dlist = treeto_list(root);
	tnode *dlist = tree_to_list2(root);
	travel_dlist(dlist);
	return 0;
}
