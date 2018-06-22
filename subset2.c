/*
ID: afluria1
LANG: C
TASK: subset
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

//first index: sequence from 1 to n
//second index: how many ways to sum to p given a sequence 1 to n
unsigned long int table[40][781];
// table[n][p]

void dp(int nTarget)
{
	int sum, n, p;
	memset(table, 0, 40*781*sizeof(unsigned long int));
	
	for(n=1; n< 40; n++)
		table[n][1] = 1;
	for(p=2; p < 781; p++)
		table[1][p] = 0;
	
	for(n=2; n <= nTarget; n++)
	{
		assert( n >= 0 && n < 40);
		for(p=2, sum = n*(n+1)/2; p <= sum; p++)
		{
			assert(p >= 0 && p < 781);
			if(p < n)
				table[n][p] = table[n-1][p];
			else if(n == p)
				table[n][p] = table[n-1][p] +1;
			// p > n to p <= sum(n)
			else
				table[n][p] = table[n-1][p] + table[n-1][p-n];
		}
	}
}


int main()
{
	int n;
	FILE *fin=fopen("subset.in", "r"), *fout=fopen("subset.out", "w");
	assert(fin != NULL && fout != NULL);
	fscanf(fin, "%d", &n);
	if((n*(n+1)/2) %2 != 0)
	{
		fprintf(fout, "0\n");
		exit(0);
	}
	dp(n);
	//printf("%d\n", table[39][780]);
	fprintf(fout, "%d\n", table[n][n*(n+1)/4]/2);
	exit(0);
	
	
}