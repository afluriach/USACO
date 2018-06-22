/*
ID: afluria1
LANG: C
TASK: checker
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int solutions[3][13];
int nSolutions=0;

typedef struct
{
	//store the col pos for each row.
	long long int row : 52;
	unsigned int c :13;
	unsigned int p :25;
	unsigned int n :25;
} BoardState;

void clearBoard(BoardState * b)
{
	memset(b, 0, sizeof(BoardState));
}

void handleSolution(BoardState * b, int n)
{
	int i;
	if(nSolutions < 3)
		for(i=0;i<n;i++)
			
			solutions[nSolutions][i] = ((b->row >> i*4) & 15)+1;
	nSolutions++;
}

void traverse(int rowIndex, int n, BoardState * b)
{
	//printf("Entering row %d\n", rowIndex);
	if(rowIndex == n){
		handleSolution(b, n);
		return;
	}
		//use zero based index for row. solution found
	int i;
	for(i=0;i<n; i++)
	{
		//if the column, positive diagonal, or negative diagonal is already filled
		if(((b->c >> i)&1) || (b->p >>(rowIndex+i)&1) || (b->n >> (n-rowIndex+i))&1)
			continue;
		else
		{
			BoardState * bn = malloc(sizeof(BoardState));
			assert(bn != NULL);
			memcpy(bn, b, sizeof(BoardState));
			long long x = i;
			b->row |=   x << rowIndex*4;
			b->c |= 1 << i;
			b->p |= 1 << (rowIndex+i);
			b->n |= 1 << n-rowIndex+i;
			traverse(rowIndex+1, n, bn);
			/*
		b->c &= !(1 << i);
		b->p &= !(1 << (rowIndex+i));
		b->n &= !(1 << (n-rowIndex+i));
		*/
			
		}
	}
	
}

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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