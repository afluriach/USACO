/*
ID: afluria1
LANG: C
TASK: milk3
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int aCap, bCap, cCap;
int results[100], nResults;
char * table;
char * tableCell(int a, int b, int c){
	char * start = table;
	start += a*(bCap+1)*(cCap+1);
	start += b*(cCap+1);
	start += c;
	return start;
}

void popResults()
{
	nResults = 0;
	int b, c;
	
	for(c=0;c<= cCap; c++)
		if(*tableCell(0, cCap - c, c))
			results[nResults++] = c;
	/*
	for(b=0;b<=bCap; b++)
		for(c=0;c<=cCap; c++)
		{
			if(*tableCell(0, b, c))
				results[nResults++] = c;
		}
	*/
}

void pour(int a, int b, int c)
{
	assert(a >= 0 && a <= aCap);
	assert(b >= 0 && b <= bCap);
	assert(c >= 0 && c <= cCap);
	if(*tableCell(a,b,c))
		return;
	*tableCell(a,b,c) = 1;
	
	//pour a into b
	b + a <= bCap ? pour(0, b+a, c) : pour(a - (bCap - b), bCap, c);
	//pour a into c
	c + a <= cCap ? pour(0, b, c+a) : pour(a - (cCap - c), b, cCap);
	//pour b into a
	a + b <= aCap ? pour(a+b, 0, c) : pour(aCap, b - (aCap - a), c);
	//pour b into c
	b+c <= cCap ? pour(a, 0, c+b) : pour(a, b - (cCap - c), cCap);
	//pour c into a
	a+c <= aCap ? pour(a+c, b, 0) : pour(aCap, b, c - (aCap - a));
	//pour c into b
	c+b <= bCap ? pour(a, b+c, 0) : pour(a, bCap, c - (bCap - b));
}

int main()
{
	FILE * fin = fopen("milk3.in", "r"), *fout = fopen("milk3.out", "w");
	if(fin == NULL || fout == NULL){
		printf("I/O file error\n");
		exit(0);
	}
	fscanf(fin, "%d %d %d", &aCap, &bCap, &cCap);
	table = calloc((aCap+1) * (bCap+1)*(cCap+1), sizeof(char));
	assert(table != NULL);
	pour(0, 0, cCap);
	
	int isFirst, i;
	popResults();
	for(i=0, isFirst=1; i < nResults; i++)
	{
		if(!isFirst)
			fprintf(fout, " ");
		fprintf(fout, "%d", results[i]);
		isFirst = 0;
	}
	fprintf(fout, "\n");
	exit(0);
	
}