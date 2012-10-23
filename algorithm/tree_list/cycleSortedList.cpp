#include <iostream>
#include <assert.h>

typedef struct node{
	int val;
	struct node *next;
}node, *pnode;

/**
 * @brief 
 *
 * @param p the head of the list, 
 * @param val the insert val
 *
 * @return  we always return the head of the list
 */
pnode insert(pnode p, int val)
{
	if(p == NULL){
		pnode tmp= new node();
		tmp->val = val;
		tmp->next = tmp;
		return tmp;	
	}else{
		pnode cur = p, pre = NULL;
		bool retInsert = false;

		if(cur->val < val){
			pre = cur;
			cur = cur->next;
		}

		while(cur != p && cur->val < val){
			pre = cur;
			cur = cur->next;
		}

		if(pre == NULL){
			pre = cur;
			while(pre->next != p)
				pre = pre->next;
			retInsert = true;
		}

		pnode tmp= new node();
		tmp->val = val;
		pre->next = tmp;
		tmp->next = cur;	
		if(retInsert)
			return tmp;
		return p;
	}
}
using namespace std;
void printList(pnode p)
{
	assert(p != NULL);
	pnode cur = p;
	while(cur->next != p){
		cout<<cur->val<<"\t";
		cur = cur->next;
	}
	cout<<cur->val<<endl;
}
int main()
{
	int array[] = {	1, 2, 3, 5, 4, 0 };
	pnode p = insert(NULL, array[0]);
	int len = sizeof(array) / sizeof(array[0]);
	for(int i = 1; i < len ; i++){
		printList(p);
		p = insert(p, array[i]);
	}
	printList(p);
	return 0;
}
