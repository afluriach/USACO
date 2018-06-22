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
#define max(a,b,c) max2(max2(a,b),c)
#define max2(a,b) ((a > b) ? (a) : (b))



typedef struct
{
    int x, y;
}vertex;





typedef struct SetNode{
	short int count, isRoot, height, fieldID;
	struct SetNode * parent;
    double diameter;
} SetNode;

SetNode * getRoot(SetNode * s);
    SetNode fields[150];

int isDisjoint(SetNode * a, SetNode * b)
{
    return !(getRoot(a) == getRoot(b));
}


SetNode * getRoot(SetNode * s)
{
	//printf("getting root of room %d-%d\n", s->x, s->y);
	while(!s->isRoot){
		s = s->parent;
		//printf("getting root of room %d-%d\n", s->x, s->y);
	}
//	printf("it is room %d-%d\n", s->x, s->y);
	return s;
}

int getCount(SetNode * s)
{
	//printf("count: %d root count %d\n", s->count, getRoot(s)->count);
	return getRoot(s)->count;
}
void join(SetNode *a, SetNode * b)
{
	SetNode * aR = getRoot(a);
	SetNode * bR = getRoot(b);

	if(aR == bR){
		//printf("join not completed\n");
		return;
	}
	bR->parent = aR;
	bR->isRoot = 0;
	int total = aR->count + bR->count;
	aR->count = bR->count = total;


}

vertex coords[150];
double adj[150][150];
//store the distance of the longest path to a reachable vertex
double farthest[150];
int nVerticies;

void setDiameter(int field)
{
    int i, j;
    double max = 0;
    for(i=0;i<nVerticies;i++)
    {
        if(isDisjoint(fields+field, fields+i))
            continue;
        for(j=0;j<nVerticies;j++)
        {
            if(isDisjoint(fields+field, fields+j))
                continue;
            else if(adj[i][j] > max && adj[i][j] < 100000)
                max = adj[i][j];

        }
    }
    fields[field].diameter = max;
}

double dist(int i, int j)
{
    return sqrt(sq(coords[i].x-coords[j].x) + sq(coords[i].y-coords[j].y));
}

void addEdge(double arr[150][150], int i, int j)
{
    arr[i][j] = dist(i,j);
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

double fieldDiameter(SetNode * s)
{
    return getRoot(s)->diameter;
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
        fields[i].isRoot = 1;
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

    //double init[150][150];
    //memcpy(init, adj, 150*150*sizeof(double));

    warshall(adj);

    //each vertex will be in its own set. join by adjacency

    for(i=0;i<nVerticies;i++)
    {
        for(j=0;j<nVerticies;j++)
        {
            if(adj[i][j] < 100000)
                join(fields+i, fields+j);
        }
    }

    //find the diameter of each field

    for(i=0;i<nVerticies;i++)
    {
        if(fields[i].isRoot)
            setDiameter(i);
    }

    //find farthest

    for(i=0;i<nVerticies;i++)
    {
        double max=0;
        for(j=0;j<nVerticies;j++)
        {
            if(adj[i][j] < 100000 && adj[i][j] > max)
                max = adj[i][j];
        }
        farthest[i] = max;
    }

    double temp;
    double shortest=1000000000;
    for(i=0;i<nVerticies;i++)
    {
        for(j=0;j<nVerticies;j++)
        {
            if(isDisjoint(fields+i, fields+j)){
                temp = max(farthest[i]+farthest[j]+dist(i,j), fieldDiameter(fields+i), fieldDiameter(fields+j));
                //printf("Considering %d and %d. New field would be %lf.\n", i, j, temp);
                if(temp < shortest)
                    shortest = temp;
            }
        }
    }




    fprintf(fout, "%.6lf\n", shortest);

	exit(0);
}
