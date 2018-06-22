/*
ID: afluria1
LANG: C
TASK: numtri
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void addRow(int crntRowNum, int rowMax, int crntRowIndex, int * arr)
{
	if(crntRowNum == rowMax)
		return;
	addRow(crntRowNum+1, rowMax, crntRowIndex+crntRowNum, arr);
	int nextRowIndex = crntRowIndex + crntRowNum, i;
	for(i=0;i<crntRowNum;i++)
	{
		arr[i+crntRowIndex] += arr[nextRowIndex+i] > arr[nextRowIndex+i+1] ? arr[nextRowIndex+i] : arr[nextRowIndex+i+1];
	}
}

int main()
{
	FILE *fin = fopen("numtri.in", "r"), *fout = fopen("numtri.out", "w");
	assert(fin != NULL && fout != NULL);
	
	int nRows, *arr;
	fscanf(fin, "%d", &nRows);
	int i, nNodes = nRows * (nRows+1) / 2;
	arr = malloc(sizeof(int) * (nNodes + 1));
	assert(arr != NULL);
	
	for(i=1; i <= nNodes; i++)
		fscanf(fin, "%d ", arr+i);
	
	addRow(1, nRows, 1, arr);
	fprintf(fout, "%d\n", arr[1]);
	exit(0);
}