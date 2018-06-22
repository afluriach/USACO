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

#define min(a,b) ((a<b) ? (a) : (b))

//stores whether or not it is possible to make a given amount of change
//in the first element, and the minimum number of coins required in the second
//element

unsigned char isPossible[MAX_VALUE], minRequired[MAX_VALUE];
int stamps[MAX_STAMP_TYPES];

int main()
{
	FILE *fin=fopen("stamps.in", "r"), *fout=fopen("stamps.out", "w");
	assert (fin!= NULL && fout != NULL);

    int nValues, nStampsUsed, i, j, k, largestStampValue=0, maxValue;
    fscanf(fin, "%d%d", &nStampsUsed, &nValues);

    isPossible[0] = 1;
    minRequired[0] = 0;

    for(i=1;i<= MAX_VALUE;i++){
        isPossible[i] = 0;
    }

    for(i=0;i<nValues;i++){
        fscanf(fin, "%d", stamps+i);
        if(stamps[i] > largestStampValue)
            largestStampValue = stamps[i];
    }

    maxValue = largestStampValue * nStampsUsed;

    for(i=0;i<nValues; i++)
    {
        for(k=0;k<=maxValue;k++)
        {
            if(k >= stamps[i] && isPossible[k-stamps[i]] && minRequired[k-stamps[i]] < nStampsUsed){
                if(!isPossible[k])
                {
                    isPossible[k] = 1;
                    minRequired[k] = minRequired[k-stamps[i]]+1;
                }
                else
                    minRequired[k] = min(minRequired[k],minRequired[k-stamps[i]]+1);
            }
        }
    }

    for(i=1;i<MAX_VALUE;i++)
    {
        if(!isPossible[i])
            break;
    }
    fprintf(fout, "%d\n", i-1);
	exit(0);
}
