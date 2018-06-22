/*
ID: afluria1
LANG: C
TASK: comehome
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define plotNum(a) ( (a >= 'a' && a <= 'z') ? (a - 'a') : ( a - 'A'+26) )
#define plotChar(a) ( ( a >= 0 && a < 26 ) ? (a+'a') : (a -26 + 'A') )
#define INFINITY 10000000
#define MIN(a,b) ((a<b) ? (a) : (b))

int adj[52][52];

int main()
{
	FILE *fin=fopen("comehome.in", "r"), *fout=fopen("comehome.out", "w");
	assert (fin!= NULL && fout != NULL);
	
	int nEdges, i, j, k;
	fscanf(fin, "%d", &nEdges);
	
    for(i=0;i<52;i++)
        for(j=0;j<52;j++)
            adj[i][j] = INFINITY;



    for(i=0;i<nEdges; i++)
	{
        char a, b;
        int weight;
        fscanf(fin, " %c %c %d ", &a, &b, &weight);
        //printf("Added edge from %c to %c (%d to %d).\n", a, b, plotNum(a), plotNum(b));
        
        adj[plotNum(a)][plotNum(b)] = MIN(weight, adj[plotNum(a)][plotNum(b)]);
        adj[plotNum(b)][plotNum(a)] = MIN(weight, adj[plotNum(b)][plotNum(a)]);
    }
    

    //warshalls algorithm

    for(k=0;k<52;k++)
    for(i=0;i<52;i++)
    for(j=0;j<52;j++)
        adj[i][j] = MIN(adj[i][j] , adj[i][k] + adj[k][j]);

    //find closest one that has a cow (capital other than Z)
    
    int  plot;
    int min=INFINITY;
    
    for(i=plotNum('A');i<plotNum('Z'); i++)
    {
        //printf("%c %d\n", plotChar(i), adj[i][plotNum('Z')]);
        if(adj[i][plotNum('Z')] < min)
        {
                plot = i;
                min = adj[i][plotNum('Z')];
        }
    }
    fprintf(fout, "%c %d\n", plotChar(plot), min);

	
	exit(0);
}
