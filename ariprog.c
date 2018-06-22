/*
ID: afluria1
LANG: C
TASK: ariprog
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sq[251];
short int isBsq[125001];

int found[10000][2];
int fIndex=0;

void popSq(){
	int i;
	for(i=0;i<=250;i++)
		sq[i] = i*i;
}


void popIsBsq(int max){
	memset(isBsq, 0, sizeof(short int)*125001);
	int i, j;
//	for(i=0;i<125001; i++)
//		isBsq[i] = 0;
	for(i=0; i<=max; i++)
		for(j=0;j<=max;j++)
			isBsq[sq[i]+sq[j]] = 1;
}

void printIsBsq(int start, int end, int delta){
	for(; start <= end; start += delta)
		printf("%d: %s\n", start, isBsq[start] ? "true" : "false" );
}

void addResult(int first, int delta){
	found[fIndex][0] = first;
	found[fIndex++][1] = delta;
}

int cmpSq(const void * a, const void * b){
	const int * x = a;
	const int * y = b;
	
	if(x[1] < y[1])
		return -1;
	else if (x[1] > y[1])
		return 1;
	else
	{
		if(x[0] < y[0])
			return -1;
		else if(x[0] > y[0])
			return 1;
		else return 0;
	}
}

void sortResult(){
	qsort(found, fIndex, sizeof(int) * 2, cmpSq);
}

void printResult(FILE * fout){
	int i;
	for(i=0;i<fIndex;i++)
		fprintf(fout, "%d %d\n", found[i][0], found[i][1]);
}

int main()
{
	FILE * fin = fopen("ariprog.in", "r"), *fout = fopen("ariprog.out", "w");
	if(fin == NULL || fout == NULL){
		printf("I/O file error\n");
		exit(0);
	}
	
	int len, max, maxBisq, i, j, k;
	fscanf(fin, "%d", &len);
	fscanf(fin, "%d", &max);
	maxBisq = 2*max*max;
	
	popSq();
	popIsBsq(max);
	
	//i is start of sequence and j is the delta of the sequence
	
	for(i=0;i<maxBisq; i++)
	{
		//printf("testing start:%d\n", i);
		for(j=1;i+(len-1)*j <= maxBisq; j++)
		{
			//printf("\ttesting delta: %d\n", j);
			int found=1;
			for(k=0;k<len && i+j*k <= maxBisq;k++)
				if(!isBsq[i+j*k]){
					found=0;
					break;
				}
			if(found)
				addResult(i, j);
		}
	}
	sortResult();
	fIndex > 0 ? printResult(fout) : fprintf(fout, "NONE\n");
	exit(0);
}