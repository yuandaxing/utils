//this is not for a general list sorting algorithm
//just domenstrate how to do it
#include <stdio.h>
#include <stdlib.h>

typedef struct node_ {
	int data;
	struct node_ *next;
	node_( int d, struct node_ *n = NULL ) : 
		data(d), next(n) { }
} node_t;

node_t * merge( node_t *h1, node_t *h2 ) {
	node_t *head = NULL, *tail = NULL;

	if( h1 == NULL || h2 == NULL )
		return h1 == NULL ? h2 : h1;

	while( h1 != NULL && h2 != NULL ) {
		node_t *temp = NULL;
		if( h1->data < h2->data ) {
			temp = h1;
			h1 = h1->next;
		} else {
			temp = h2;
			h2 = h2->next;
		}

		temp->next = NULL;
		//add temp to list
		if( head == NULL )
			head = temp;

		if( tail == NULL ) {
			tail = temp;
		} else {
			tail->next = temp;
			tail = temp;
		} 
	}

	if( h1 != NULL )
		tail->next = h1;
	else if( h2 != NULL ) 
		tail->next = h2;

	return head;
}

const int len = 64;
node_t * listSorting( node_t *h ) {
	node_t *hl[len] = { 0 };

	while( h != NULL ) {
		node_t *next = h->next;
		h->next = NULL;

		for( int i = 0; i < len; i++ ) {
			if( hl[i] != NULL ) {
				h = merge( h, hl[i] );
				hl[i] = NULL;
			} else {
				hl[i] = h;
				break;
			}
		}

		h = next;
	}

	for( int i = 0; i < len; i++ ) {
		if( hl[i] != NULL ) {
			h = merge( h, hl[i] );
			hl[i] = NULL;
		}
	}

	return h; 		  
}

void printList( node_t *h ) {
	while( h != NULL ) {
		printf( "%d ", h->data );
		h = h->next;
	} 
}
int main() {
// test 1
	node_t n1(10), n2(0, &n1), n3(2, &n2), n4(3, &n3), n5(1, &n4);
	printList( &n5 );
	printf( "\n" );
	node_t *h = listSorting( &n5 );
	printList( h );
	printf( "\n" );

//test 2;
	node_t *h2 = NULL;
	printf( " this is a test for round 2\n " );
	printList( listSorting( h2 ) );
	
	printf( "\nend round 2\n" );


//test round 3 
	node_t n6(2), n7(4, &n6), n8(5, &n7);
	printf( " this is a test for round 3 \n" );
	printList( listSorting( &n8 ) );
	printf( " \nend for round 3\n" );
	
	return 0;
}
