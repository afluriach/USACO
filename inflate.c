/*
ID: afluria1
LANG: C
TASK: inflate
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_L 10001
#define MAX_N 10001
#define MAX(a,b) ((a>b) ? (a) : (b))

int main()
{
	FILE *fin=fopen("inflate.in", "r"), *fout=fopen("inflate.out", "w");
	assert (fin!= NULL && fout != NULL);
	int i, j, contestLength, nTypes, typeLen[MAX_N], typeScore[MAX_N], dp[2][MAX_N], crnt, prev;
	
	fscanf(fin, "%d %d", &contestLength, &nTypes);
	
	for(i=0;i<nTypes;i++)
	{
		fscanf(fin, "%d %d ", typeScore+i, typeLen+i);
	}
	
	
	//for the dp, only the current and previous row of the matrix are actually needed.
	//with the start of each new type, crnt -> prev row 
	
	//base case: considering no activity means zero points for any given time:
	//also clear the crnt row
	//memset(dp, 0, MAX_N*sizeof(int));
	//memset(dp+1, 0, MAX_N*sizeof(int));
	crnt = 0;
	prev = 1;
	
	for(i=0;i<nTypes;i++)
	{
		crnt ^= 1;
		prev ^= 1;
		assert(crnt == 1 || crnt==0); assert(prev == 1 || prev==0); assert(crnt != prev);
		for(j=0;j<=contestLength; j++)
		{
			if(j<typeLen[i])
				dp[crnt][j] = dp[prev][j];
			else
				dp[crnt][j] = MAX(dp[prev][j], dp[crnt][j-typeLen[i]]+typeScore[i]);
		}
	}
	
	fprintf(fout, "%d\n", dp[crnt][contestLength]);
	
	exit(0);
}