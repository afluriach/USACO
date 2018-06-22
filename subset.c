/*
ID: afluria1
LANG: C
TASK: subset
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int state[40], count=0, n, sum=0;

void printComb()
{
	int i;
	for(i=1;i<=n;i++)
		if(state[i])
			printf("%d, ", i);
	printf(" - ");
	for(i=1;i<=n;i++)
		if(!state[i])
			printf("%d ", i);
	printf("\n");
	
}

int recIter(int crnt, int lPart, int rPart)
{
	if(crnt==0)
		return lPart==rPart ? 1 : 0;
	int l = recIter(crnt-1, lPart+crnt, rPart);
	int r = recIter(crnt-1, lPart, rPart+crnt);
	return l + r;
}

void iter(int crnt, int targetSum)
{
	//printComb();
	if(crnt == n+1)
	{
		if(sum == targetSum)
			count++;
		return;
	}
	if(sum > targetSum)
		return;
	state[crnt] =1;
	sum += crnt;
	iter(crnt+1, targetSum);
	state[crnt] = 0;
	sum -= crnt;
	iter(crnt+1, targetSum);
}

int main()
{
	int total;
	FILE *fin=fopen("subset.in", "r"), *fout=fopen("subset.out", "w");
	fscanf(fin, "%d", &n);
	memset(state+1, 0, n*sizeof(int));
	total = n*(n+1)/2;
	//iter(1, total/2);
//	fprintf(fout, "%d\n", count/2);
	fprintf(fout, "%d\n", recIter(n, 0, 0)/2);
	exit(0);
}