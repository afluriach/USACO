/*
ID: afluria1
LANG: C
TASK: maze1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_W 38
#define MAX_H 100
#define INFIN 1000000
#define min(a,b) ((a < b) ? (a) : (b))
#define max(a,b) ((a > b) ? (a) : (b))

//index nVerticies represents the exit vertex
//the two cells that have exits will have
//a cost of one to this node.
unsigned char adj[MAX_W*MAX_H+1][MAX_W*MAX_H+1];

int w, h, n;

int v(int x, int y){
    return y*w + x;
}

void addEdge(int x1, int y1, int x2, int y2)
{
    //printf("Edge created %d,%d\n", v(x1, y1),v(x2, y2));
    adj[v(x1, y1)][v(x2, y2)] = 1;
    adj[v(x2, y2)] [v(x1, y1)]= 1;
}

void addExit(int x, int y)
{
    //printf("Exit created %d\n", v(x,y));
    adj[n-1][v(x,y)] = 1;
    adj[v(x,y)][n-1] = 1;
}



void parseTopLine(char * line, int rowNum)
{
    assert(*line != '\0');
    int i;
    for(i=0;i<w; i++, line++)
    {
        assert(*line == '+');
        line++;
        if(*line == ' ')
        {
            if(rowNum != 0) addEdge(i, rowNum, i, rowNum-1);
            else addExit(i,rowNum);
        }
        else continue;
    }
}

void parseLastLine(char * line)
{
    assert(*line != '\0');
    int i;
    for(i=0;i<w; i++, line++)
    {
        assert(*line == '+');
        line++;
        if(*line == ' ')
            addExit(i,h-1);
    }
}
void parseBottomLine(char * line, int rowNum)
{
    assert(*line != '\0');
    int i;
    for(i=0;i<w;i++, line += 2)
    {
        if(*line == ' '){
            if(i != 0)
                addEdge(i, rowNum, i-1, rowNum);
            else
                addExit(i, rowNum);
        }
            
    }
    
    //for right edge of last one
    if(*line == ' '){
        addExit(w-1, rowNum);
    }
}

int main()
{
	FILE *fin=fopen("maze1.in", "r"), *fout=fopen("maze1.out", "w");
	assert (fin!= NULL && fout != NULL);

    int i, j, k;
    char line[200];

    fscanf(fin, "%d%d ", &w, &h);

    //the last node (index h*w) is the exit node.
    //initially only the exit cells are adjacent to it.

    n = h*w + 1;

        for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            adj[i][j] = INFIN;
    
    for(i=0;i<h; i++)
    {
        fgets(line, 200, fin);
        parseTopLine(line, i);
        fgets(line, 200, fin);
        parseBottomLine(line, i);
    }
    fgets(line, 200, fin);
    parseLastLine(line);
    
    for(k=0;k<n;k++)
    for(i=0;i<n;i++)
    for(j=0;j<n;j++)
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

    int largest=0;

    for(i=0;i<n-1; i++)
        largest = max(largest, adj[i][n-1]);

    fprintf(fout, "%d\n", largest);
	exit(0);
}
