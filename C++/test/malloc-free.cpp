/*
 * =====================================================================================
 *
 *       Filename:  malloc-free.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年04月24日 08时26分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yuan DaXing (http://hi.baidu.com/%E8%A2%81%E5%A4%A7%E6%98%9F/home), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define ITEM_SIZE (sizeof(item) - sizeof(void *))

typedef struct item{
	uint16_t size;
	union {
		char mem[4];
		struct item *next;
	}mn;
}__attribute__ ((packed)) item;

static item *freelist=NULL;
void init(void *memory, uint16_t size) 
{
	assert(memory != NULL && size > sizeof(item));

	freelist = (item *) memory;
	freelist->mn.next = NULL;
	freelist->size = size - ITEM_SIZE;
}

static bool cut(item *it, uint16_t size, item **n)
{
	assert(it != NULL && n != NULL);

	if((uint16_t) (it->size - size) < (uint16_t) sizeof(item))
		return false;

	*n = (item *)(it->mn.mem + size);
	(*n)->size = it->size - size - ITEM_SIZE;
	(*n)->mn.next = it->mn.next;
	it->size = size;
	return true;
}

static void splice(item *left, item *right)
{
	if(left == NULL || right == NULL)
		return ;
	char *start = left->mn.mem + left->size;
	if(start != (char *)right)
		return ;
	left->size = left->size + right->size + ITEM_SIZE;
	left->mn.next = right->mn.next;
}

void * malloc(uint16_t size) 
{

	if(size < 4)
		size = 4;

	item *prev = NULL, *cur = freelist;
	item *n = NULL;

	while(cur != NULL) {
		if(cur->size > size) {
			bool c = cut(cur, size, &n);
			if(c == false)
				n = cur->mn.next;

			if(prev == NULL)
				freelist = n;
			else
				prev->mn.next = n;

			return cur->mn.mem;
		}
		prev = cur;
		cur = cur->mn.next;
	}

	return NULL;
}

void free(void *p)
{
	if(p == NULL)
		return ;
	item *cur = freelist, *prev = NULL;
	item *pit = (item *)((char *)p - ITEM_SIZE);
	while(cur != NULL) {

		if(cur > pit) {
			if(prev == NULL) {
			       pit->mn.next = freelist;
		       	       freelist = pit;
			} else {
				pit->mn.next = prev->mn.next;
				prev->mn.next = pit;
			}		
				
			splice(pit, cur);
			splice(prev, pit);
			return ;
		}
		prev = cur;
		cur = cur->mn.next;
	}

	if(prev == NULL) {
		pit->mn.next = freelist;
		freelist = pit;
	} else {
		pit->mn.next = prev->mn.next;
		prev->mn.next = pit;
	}		
	splice(prev, pit);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
#define	K_1	1024
#define K_64	(K_1 * 20)
char memory[K_64]; 

		int
main ( int argc, char *argv[] )
{
	init(memory, K_64);

	const int count = 100000;
	void *p[count];
	int len = 0;

	for(int i = 1; i < count; i++) {
		p[len++] = malloc(i);
	}

	for(int i = 0; i < len; i++) {
		free(p[i]);
	}

	len = 0;
	for(int i = 1; i < count; i++) {
		p[len++] = malloc(i % 20 );
	}
	assert(freelist == NULL);

	for(int i = 0; i < len; i = i + 2) {
		free(p[i]);
	}
	for(int i = 1; i < len; i = i + 2) {
		free(p[i]);
	}

	assert(freelist->size == K_64 - ITEM_SIZE);
	assert(freelist->mn.next == NULL);

	printf("sizeof(item):%d\n", sizeof(item));
	return 0;
}				/* ----------  end of function main  ---------- */
