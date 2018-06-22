/*
ID: afluria1
LANG: C
TASK: stamps
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_VALUE 2000000
#define MAX_STAMPS_USED 200
#define MAX_STAMP_TYPES 50

//stores whether or not it is possible to make a given amount of change
//using a given number of coins. there is no separate dimension for
//each stamp.

char dp[MAX_STAMPS_USED+1][MAX_VALUE];
int stamps[MAX_STAMP_TYPES];

int main()
{
	FILE *fin=fopen("stamps.in", "r"), *fout=fopen("stamps.out", "w");
	assert (fin!= NULL && fout != NULL);

    int nValues, nStampsUsed, i, j, k, largestStampValue=0, maxValue;
    fscanf(fin, "%d%d", &nStampsUsed, &nValues);

    for(i=0;i<= nStampsUsed;i++){
        dp[i][0] = 1;
        for(j=1;j<MAX_VALUE; j++)
            dp[i][j] = 0;
    }

    for(i=0;i<nValues;i++){
        fscanf(fin, "%d", stamps+i);
        if(stamps[i] > largestStampValue)
            largestStampValue = stamps[i];
    }

    maxValue = largestStampValue * nStampsUsed;

    for(i=0;i<nValues; i++)
    {
        for(j=1;j<=nStampsUsed; j++)
        {
            for(k=0;k<maxValue;k++)
            {
                if(dp[j][k])
                    continue;
                //if it's possible to make a given amount using
                //j-1 coins, it's also possible with j coins
                if(dp[j-1][k])
                    dp[j][k]=1;
                //alternately, if it's possible to make k minus the
                //denomination in consideration using j-1 coins, then
                //it is also possible
                if(k >= stamps[i] && dp[j-1][k-stamps[i]])
                    dp[j][k] = 1;

            }
        }
    }

    int contig = 0;
    for(i=1;i<MAX_VALUE;i++, contig++)
    {
        if(!dp[nStampsUsed][i])
            break;
    }
    fprintf(fout, "%d\n", contig);
	exit(0);
}
