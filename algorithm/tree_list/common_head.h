#include <iostream>

using namespace std;
typedef struct list{
	int data;
	struct list *next;
}list, plist;

typedef struct tree{
	int data;
	struct tree *left, *right;
}tnode, *ptnode;

static inline void travel(list *h)
{
	while(h != NULL){
		cout<<h->data<<"\t";
		h = h->next;
	}
	cout<<endl;
}

static inline list *construct(int A[], int len)
{
	list *head = NULL, *pre = NULL;
	for(int i = 0; i < len; i++){
		list * n = new list();
		if(n == NULL){
			cout<<"oom\n";
			exit(0);
			return NULL;
		}
		n->data = A[i];
		n->next = NULL;
		if(pre){
			pre->next = n;
		}else{
			head = n;
		}

		pre = n;
	}
	return head;
}


static void pre_travel(tnode * n)
{
	if(n == NULL)
		return ;

	cout<<n->data<<"  ";
	pre_travel(n->left);
	pre_travel(n->right);
}

static void in_travel(tnode *n)
{
	if(n == NULL)
		return ;

	in_travel(n->left);
	cout<<n->data<<"  ";
	in_travel(n->right);
}
