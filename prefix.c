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


int dp[200001], seqLen, nPrims, max;
char seq[200002], prim[201][11];

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
			strcpy(prim[nPrims++], temp);
	}
	
	//printf("%d\n", nPrims);
	seqLen = 0;
	while(fscanf(fin, "%s", seq+seqLen)==1)
	{
		seqLen += strlen(seq+seqLen);
	//	printf("%d\n", seqLen);
	}
	
	max = 0;
	dp[0] = 1;
	
	for(i=0; i< seqLen; i++)
	{
        for(j=0;j<nPrims; j++)
        {
            if(dp[i] && sscmp(prim[j], seq+i) && strlen(prim[j]) +i <= seqLen)
            {
                dp[i+strlen(prim[j])] = 1;
                max = MAX(max, i+strlen(prim[j]));
                //printf("i: %d, max: %d\n",i , max);
            }
        }
    }


	fprintf(fout, "%d\n", max);
	
	exit(0);
}

