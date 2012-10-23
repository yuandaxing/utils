#include <iostream>
using namespace std;

/* 
   There are n coins in a line. (Assume n is even). Two players take turns to take a coin from one 
   of the ends of the line until there are no more coins left. The player with the larger amount of money wins.
   Would you rather go first or second? Does it matter?
   Assume that you go first, describe an algorithm to compute the maximum amount of money you can win.
*/


/*
f[0][n - 1] = max{ sum[0][n-1] - f[1][n - 1], sum[0][n - 1] - f[0][n - 2]}
sum[i][j] = sigma(s[j]) - sigma(s[i])
 */

#define N  100
int f[N][N];
int s[N];

void preProcess(int coins[], int len)
{
	if(len < 1)
		return ;
	s[0] = coins[0];
	for(int i = 1; i < len; i++){
		s[i] = s[i - 1] + coins[i];
	}
}

int DP(int coins[], int len)
{
	preProcess(coins, len);
	for(int i = 0; i < len; i++)
		f[i][i] = coins[i];

	int sum = 0;
	for(int i = 2; i <= len; i++){
		for(int j = 0; j < len; j++){
			if(j == 0)
				sum = s[j + i - 1];
			else 
				sum = s[j + i - 1] - s[j - 1]; 

			f[j][j + i - 1] = sum - min(f[j + 1][j + i - 1], f[j][j + i - 2]);
		}
	}
	return f[0][len - 1];
}

int main()
{
	int coins[] = { 3, 2, 2, 3, 1, 2 };
	int len = sizeof(coins) / sizeof(coins[0]);
	cout<<DP(coins, len)<<endl;
}
