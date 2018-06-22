/*
ID: afluria1
LANG: C
TASK: lamps
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


//using a one based index - true equals on for states, or required to be on or off respectively
int lampStates[16][101], nLamps, nCounts, finalStateOn[101], finalStateOff[101];
int finalStates[16][101], nFinals;

void printLamp(int n)
{
	int j;
	for(j=1;j<=nLamps; j++)
		{
			printf( "%c", (finalStates[n][j] ? '1' : '0'));
		}
		printf("\n");
}

void popStates()
{
	int i, j;
	for(i=0;i<16;i++)
	{
		//all lamps start out on
		memset(lampStates[i], 0xFF, 101*sizeof(int));
		if( i  & 1)
			for(j=0;j<=nLamps; j++)
				lampStates[i][j] =  !lampStates[i][j];
		if(i >>1 & 1)
			for(j=1;j<=nLamps;j+=2)
				lampStates[i][j] =  !lampStates[i][j];
		if(i>>2 & 1)
			for(j=0; j <= nLamps; j +=2)
				lampStates[i][j] =  !lampStates[i][j];
		if(i>>3 & 1)
			for(j=1; j <= nLamps; j+= 3)
				lampStates[i][j] =  !lampStates[i][j];
	}
}

int testFinal(int n)
{
	int minCount = (n&1) + (n>>1&1)+(n>>2&1) + (n>>3&1);
	int i;
	for(i=0;i<nLamps;i++)
	{
		if(finalStateOn[i] && !lampStates[n][i])
			return 0;
		if(finalStateOff[i] && lampStates[n][i])
			return 0;
		if(nCounts - minCount < 0)
			return 0;
		if((nCounts - minCount)%2 != 0)
			return 0;
	}
	return 1;
}

void filterFinalStates()
{
	int i;
	for(i=0, nFinals=0; i < 16; i++)
	{
		if(testFinal(i))
			memcpy(finalStates[nFinals++], lampStates[i], 101*sizeof(int));
	}
}

int statecmp(const void * a, const void * b)
{
	const int * x = a, *y = b;
	int i;
	for(i=1;i<=nLamps; i++)
	{
		if(!x[i] && !y[i])
			continue;
		if(x[i] && y[i])
			continue;
		if(!x[i] && y[i])
			return -1;
		if(x[i] && !y[i])
			return 1;
	}
	return 0;
}

int main()
{
	int c, i, j;
	memset(finalStateOn, 0, sizeof(int)*100), memset(finalStateOn, 0, sizeof(int)*100);
	FILE * fin = fopen("lamps.in", "r"), *fout = fopen("lamps.out", "w");
	assert(fin != NULL && fout != NULL);
	
	fscanf(fin, "%d %d", &nLamps, &nCounts);

	while(1)
	{
		fscanf(fin, "%d", &c);
		if(c == -1)
			break;
		else
			finalStateOn[c] = 1;
	}
	
	while(1)
	{
		fscanf(fin, "%d", &c);
		if(c == -1)
			break;
		else
			finalStateOff[c] = 1;
	}
	popStates();
	filterFinalStates();
	qsort(finalStates, nFinals, 101*sizeof(int), statecmp);
	
	if(nFinals == 0)
	{
		fprintf(fout, "IMPOSSIBLE\n");
		exit(0);
	}
	
	for(i=0;i<nFinals;i++)
	{
		//printLamp(i);
		for(j=1;j<=nLamps; j++)
		{
			fprintf(fout, "%c", finalStates[i][j] ? '1' : '0');
		}
		fprintf(fout, "\n");
	}
	
	exit(0);
	
}