/*
ID: afluria1
LANG: C
TASK: prefix
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX(a,b) ((a) > (b)) ? (a) : (b)

//dp: for reach primitive, it can get to the greater crntIndex+prefixLen or the value of crntIndex+prefixLen.

int dp[200001], seqLen, nPrims;
char seq[200001], prim[201][11];

int sscmp(char * a, char* b)
{
	while(1){
		if(!(*a) || !(*b))
			return 1;
		else if (*a++ != *b++)
			return 0;
	}
}




int main()
{
	FILE *fin=fopen("prefix.in", "r"), *fout=fopen("prefix.out", "w");
	
	char temp[201];
	nPrims=0;
	int i, j;
	while(1)
	{
		fscanf(fin, "%s", temp);
		if(strcmp(".", temp) == 0)
			break;
		else
			strcpy(prim[++nPrims], temp);
	}
	
	//printf("%d\n", nPrims);
	seqLen = 0;
	while(fscanf(fin, "%s", seq+seqLen)==1)
	{
		seqLen += strlen(seq+seqLen);
		//printf("%d\n", seqLen);
	}

	//BASE CASE: zero is already gaurenteed an exressible prefix. 
	
	for(i=0;i<nPrims; i++)
	{
		if(sscmp(seq, prim[i]))
			dp[strlen(prim[i])-1] = 1;
	}
	
	for(i=1; i <= seqLen; i++)
	{
		if(dp[i-1])
			for(j=0;j<nPrims; j++)
			{
				if(sscmp(seq+i, prim[j]))
					dp[i+strlen(prim[j])-1] = 1;
			}
	}
	int result=0;
	for(i=seqLen; i >= 0; i--)
		if(dp[i])
		{
			fprintf(fout, "%d\n", i-1);
			result = 1;
			break;
		}
	if(!result)
		fprintf(fout, "%d\n", 0);
	//printf("%.3s\n", seq+24191);
		
	exit(0);
}

