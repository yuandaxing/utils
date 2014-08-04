#include <stdio.h>
#include <iostream>
#include <stdlib.h>

struct evil {

	size_t operator&() {

		return 0;
	}
};

evil ev;

int main()
{
	if( true )
	{
		printf("how are you");
	}
	while( true )
	{
		break;
	}
	int i = 1;
	switch ( i )
	{
		case 1 :
			break;
		case 2 :
			break;
		default :
			break;
	}
	exit(0);

	int A[] = {
		5, 1, 2, 3, 4, 5
	};
	int result = A[0];
	int n = sizeof(A) / sizeof(A[0]);
	for(int i = 1; i < n; i++)
		result = result ^ i ^ A[i];
	printf("%d\n", result);


	printf("%u\n", &ev);
	printf("%p\n", &(char&)ev);
}
