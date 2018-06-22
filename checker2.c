/*
ID: afluria1
LANG: C
TASK: checker
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct
{
	int row[13];
	int col[13];
	int pos[25];
	int neg[25];
} BoardState;

int solutions[3][13], nSolutions=0;

void handleSolution(BoardState * b, int n)
{
	int i;
	if(nSolutions < 3)
		for(i=0;i<n;i++)
			solutions[nSolutions][i] = b->row[i]+1;
	nSolutions++;
}

void traverse(int rowIndex, int n, BoardState * b)
{
	if(rowIndex == n)
	{
		handleSolution(b, n);
		return;
	}
	int i;
	for(i=0;i<n; i++)
	{
		if(b->col[i] || b->pos[rowIndex+i] || b->neg[n-rowIndex+i-1])
			continue;
		else
		{
			b->row[rowIndex] = i;
			b->col[i] = 1;	
			b->pos[rowIndex+i] = 1;
			b->neg[n-rowIndex+i-1] = 1;
			traverse(rowIndex+1, n, b);
			b->col[i] =0;
			b->pos[rowIndex+i] = 0;
			b->neg[n-rowIndex+i-1] = 0;			
		}
	}
}


int main()
{
	FILE *fin = fopen("checker.in", "r"), *fout=fopen("checker.out", "w");
	assert(fin != NULL && fout != NULL);
	BoardState b;
	int i,j, isFirst, nRows;
	fscanf(fin, "%d", &nRows);
	memset(&b, 0, sizeof(BoardState));
	
	traverse(0, nRows, &b);
	for(i=0;i<3;i++)
	{
		for(j=0, isFirst=1;j<nRows;j++)
		{
			if(isFirst)
			{
				isFirst = 0;
			}
			else
			{
				fprintf(fout, " ");
			}
			fprintf(fout,"%d", solutions[i][j]);
		}
		fprintf(fout, "\n");
	}
	
	fprintf(fout, "%d\n", nSolutions);
	exit(0);
	
}