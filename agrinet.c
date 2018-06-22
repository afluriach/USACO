/*
ID: afluria1
LANG: C
TASK: agrinet
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_N 100
#define INFINITY 100000
#define min(a,b) ((a < b) ? (a) : (b))

int main()
{
    int adj[MAX_N][MAX_N], i, j, n, mstWeight=0, minEdge, minA, minB, mstVertCount=0;
    char inMST[MAX_N];
	FILE *fin=fopen("agrinet.in", "r"), *fout=fopen("agrinet.out", "w");
	assert (fin!= NULL && fout != NULL);

    fscanf(fin, "%d", &n);

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            fscanf(fin, "%d", &adj[i][j]);

    //arbitrarily start with vertex 0
    memset(inMST, 0, sizeof(char) * MAX_N);
    inMST[0] = 1;
    mstVertCount=1;

    //find shortest edge between a vertex in MST, and a vertex
    //out of MST
    while(mstVertCount < n){
        minEdge = INFINITY;
        for(i=0;i<n;i++)
        {
            if(!inMST[i])
                continue;
            for(j=0;j<n;j++)
            {
                if(inMST[j] || i == j)
                    continue;
                if(adj[i][j] < minEdge)
                {
                    minB = j;
                    minEdge = adj[i][j];
                }
            }
        }
        //assert(minEdge != INFINITY);
        inMST[minB] = 1;
        mstWeight += minEdge;
        mstVertCount++;
    }

    fprintf(fout, "%d\n", mstWeight);
	exit(0);
}
