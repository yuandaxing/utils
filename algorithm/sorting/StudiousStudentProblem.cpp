#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
#define N  1

int compare(const void *a, const void *b)
{
	char tmp1[20] = {0};
	char tmp2[20] = {0};
	const char **t1 = (const char **)a;
	const char **t2 = (const char **)b;
	strcpy(tmp1, *t1);
	strcat(tmp1, *t2);
	strcat(tmp2, *t2);
	strcat(tmp2, *t1);

	return strcmp(tmp1, tmp2);

}

int main()
{
	const char *p[] = {"ji", "jibw", "jijibw"};
	qsort(p, 3, sizeof(p[0]), compare);
	int len = sizeof(p) / sizeof(p[0]);
	for(int i = 0; i < len; i++)
		cout<<p[i];
	cout<<endl;
}
