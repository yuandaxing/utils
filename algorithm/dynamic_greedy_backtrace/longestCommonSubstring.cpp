#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int bruteForce(const char *a, const char *b, int *max)
{
	assert(a != NULL && b != NULL && max != NULL);
	int curLen = 0, maxstart = -1;
	int maxLen = 0;

	int lena = strlen(a), lenb = strlen(b);
	for(int i = 0; i < lena; i++){
		for(int j = 0; j < lenb; j++){
			if(a[i] == b[j]){
				int starta = i + 1;
				int startb = j + 1;
				while(starta < lena&& startb < lenb && 
						a[starta] == b[startb]){
					starta++;
					startb++;
				}
				curLen = starta - i;
				if(maxLen < curLen){
					maxLen = curLen;
					maxstart = i;
				}
			}
		}
	}

	*max = maxLen;
	return maxstart;
}
#define LEN		50
int matrix[LEN][LEN];
void DP(const char *a, const char *b)
{
	assert(a != NULL && b != NULL);

	memset(matrix, 0, sizeof(matrix));

	int lena = strlen(a), lenb = strlen(b);
	for(int i = 0; i < lena; i++){
		for(int j = 0; j < lenb; j++){
			if(a[i] == b[j]){
				if(i - 1 >= 0 && j - 1 >= 0)
					matrix[i][j] = matrix[i - 1][j - 1] + 1;
				else
					matrix[i][j] = 1;
			}
		}
	}
}

void collectOutput(const char *a, const char *b)
{
	assert(a != NULL);

	int max = 0;
	int end = -1;

	int lena = strlen(a);
	int lenb = strlen(b);
	for(int i = 0; i < lena; i++){
		for(int j = 0; j < lenb; j++){
			if(matrix[i][j] > max){
				max = matrix[i][j];
				end = i;
			}
		}
	}
	
	for(int i = 0; i < max; i++){
		printf("%c", a[end - max + 1+ i]);
	}
	printf("\n");

}

void cal(const char *a, const char *b)
{
	int maxLen, maxstart;

	maxstart = bruteForce(a, b, &maxLen);
	for(int i = 0; i < maxLen; i++)
		printf("%c", a[maxstart + i]);
	printf("\n");
}
int main()
{
	const char *a = "caba";
	const char *b = "abac";
	const char *a1 = "abacdfgdcaba";
	const char *b1 = "abacdgfdcaba";
	cal(a, b);
	cal(a1, b1); 
	DP(a, b);
	collectOutput(a, b);
	DP(a1, b1);
	collectOutput(a1, b1);

	return 0;
}
