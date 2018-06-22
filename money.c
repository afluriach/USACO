/*
ID: afluria1
LANG: C
TASK: money
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



int nDenoms, targetAmount, denoms[25];
unsigned long long int count=0, dp[26][10001];

void printTable()
{
	int i, j;
	for(i=0;i<=targetAmount; i++)
		printf("  %d", i);
	printf("\n");
	for(i=0;i<=nDenoms; i++)
	{
		printf("%d", denoms[i]);
		for(j=0;j<=targetAmount; j++)
			printf(" %d ", dp[i][j]);
		printf("\n");
	}
}

int main()
{
	int i, j;
	
	FILE *fin=fopen("money.in", "r"), *fout=fopen("money.out", "w");
	assert(fin != NULL && fout != NULL);
	fscanf(fin, "%d%d", &nDenoms, &targetAmount);
	
	for(i=1;i<=nDenoms;i++)
		fscanf(fin, "%d", denoms+i);

	//base case: there is one way to make zero cents with any denomination; zero ways to make more than zero cents with zero denomination
	denoms[0] = 0;
	for(i=0;i<=targetAmount;i++)
		dp[0][i] = 0;
	for(j=0;j<=nDenoms; j++)
		dp[j][0] = 1;
		
	for(i=1; i<= nDenoms; i++)
	{
		int crntDenom = denoms[i];
		for(j=1; j<=targetAmount; j++)
		{
			if(j < crntDenom)
				dp[i][j] = dp[i-1][j];
			else 
				dp[i][j] = dp[i][j-crntDenom]+dp[i-1][j];
		}
	}
	
	fprintf(fout, "%Ld\n", dp[nDenoms][targetAmount]);
	//printTable();
	exit(0);
}