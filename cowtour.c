/*
ID: afluria1
LANG: C
TASK: cowtour
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define sq(n) pow(n,2)
#define min(a,b) ((a < b) ? (a) : (b))

typedef struct
{
    int x, y;
}vertex;

vertex coords[150];
double adj[150][150];
int nVerticies;

void addEdge(double arr[150][150], int i, int j)
{
    arr[i][j] = sqrt(sq(coords[i].x-coords[j].x) + sq(coords[i].y-coords[j].y));
    //printf("Added endge between %d and %d; distance %lf.\n", i, j, arr[i][j]);
}

void warshall(double arr[150][150])
{
    int i, j, k;
        for ( k = 0; k < nVerticies; k++ )
          for ( i = 0; i < nVerticies; i++ )
             for ( j = 0; j < nVerticies; j++ )
                arr[i][j] = min( arr[i][j], arr[i][k] + arr[k][j] );
}

double getDiameter(int a, int b)
{
    double largest=0;
    int i, j;
    double path[150][150];
    memcpy(path, adj, 150*150*sizeof(double));

    addEdge(path, a, b);
    warshall(path);

    for(i=0;i<nVerticies;i++)
    {
        for(j=0;j<nVerticies;j++)
        {
            if(path[i][j] > largest && path[i][j] < 1000000)
                largest = path[i][j];
        }
    }
    //printf("Largest path after adding edge(%d,%d): %lf.\n", a, b, largest);
    return largest;

}

int main()
{
	FILE *fin=fopen("cowtour.in", "r"), *fout=fopen("cowtour.out", "w");
	assert (fin!= NULL && fout != NULL);

    int i, j, k;

    fscanf(fin, "%d", &nVerticies);

    for(i=0;i<nVerticies;i++)
    {
        int x,y;
        fscanf(fin, "%d%d", &x, &y);
        coords[i].x=x, coords[i].y=y;
    }
    for(i=0;i<nVerticies;i++)
    {
        for(j=0;j<nVerticies;j++)
        {
            char temp;
            fscanf(fin, "%c", &temp);
            while (temp != '0' && temp != '1')
                fscanf(fin, "%c", &temp);
            if(temp=='1'){
                addEdge(adj, i, j);
                //adj[j][i]  = adj[i][j];
            }
            else if(i==j)
                adj[i][j] = 0;
            else
                adj[i][j] = 1000000000;
        }
        //char temp;
        //fscanf(fin, "%c", &temp);
        //assert(temp == '\n');
    }

    //first, discount vertexes which are indirectly connected, then
    //consider which edge between two unconnected points will lead to the
    //narrowest graph

    double init[150][150];
    memcpy(init, adj, 150*150*sizeof(double));

    warshall(init);

    double shortest=1000000000;
    for(i=0;i<nVerticies;i++)
    {
        for(j=0;j<nVerticies;j++)
        {
            if(init[i][j] > 1000000)
            {
                shortest = min(getDiameter(i, j), shortest);
            }
        }
    }




    fprintf(fout, "%.6lf\n", shortest);

	exit(0);
}
