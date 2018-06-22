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
#define INFINITY 1000000000

#define min(a,b) ((a < b) ? (a) : (b))
#define max(a,b) ((a > b) ? (a) : (b))

typedef struct
{
    int dist;
    char l, r, u, d, known;
} node;

int w, h;

node n[MAX_H][MAX_W];

void printWalls()
{
    int i, j;
    for(i=0;i<h;i++)
    {
        for(j=0;j<w;j++)
        {
            printf("%2.d ", n[i][j].u * 8 + n[i][j].d * 4 + n[i][j].l * 2 + n[i][j].r);
        }
        printf("\n");
    }
    printf("\n");
}

void printMaze()
{
    int i, j;
    for(i=0;i<h;i++)
    {
        for(j=0;j<w;j++)
        {
            printf("%3.d ", n[i][j].dist != INFINITY ?
                    n[i][j].dist : -1);
        }
        printf("\n");
    }
    printf("\n");
    printWalls();
}

void resetKnown()
{
    int i,j;
    for(i=0;i<w;i++)
        for(j=0;j<h;j++)
            n[j][i].known = 0;
}

int isExit(int x, int y)
{
    if(y == 0 && x >0 && x < w-1)
        return n[0][x].d;
    else if(y == h-1 && x >0 && x < w-1)
        return n[h-1][x].u;
    else if(x ==0)
        return n[y][0].l;
    else if (x == w-1)
        return n[y][w-1].r;
    else return 0;
}

//should be called on an exit node with should have a distance of 1
void prop(int y, int x)
{
    int propLeft=0, propRight=0, propDown=0, propUp = 0;
    //printMaze();
    if(n[y][x].known)
        return;
    else n[y][x].known = 1;
    if(n[y][x].u && y < h-1)
    {
        if(n[y+1][x].dist > n[y][x].dist+1)
        {
            n[y+1][x].dist = n[y][x].dist + 1;
            n[y+1][x].known = 0;
            propUp = 1;
        }
    }
    if(n[y][x].d && y > 0 )
    {
         if(n[y-1][x].dist > n[y][x].dist+1)
        {
            n[y-1][x].dist = n[y][x].dist + 1;
            n[y-1][x].known = 0;
            propDown = 1;
        }
    }
    if(n[y][x].l && x > 0 )
    {
         if(n[y][x-1].dist > n[y][x].dist+1)
        {
            n[y][x-1].dist = n[y][x].dist + 1;
            n[y][x-1].known = 0;
            propLeft = 1;
        }
    }
    if(n[y][x].r && x < w-1 )
    {
         if(n[y][x+1].dist > n[y][x].dist+1)
        {
            n[y][x+1].dist = n[y][x].dist + 1;
            n[y][x+1].known=0;
            propRight = 1;
        }
    }
    if(propUp) prop(y+1, x);
    if(propDown) prop(y-1, x);
    if(propLeft) prop(y, x-1);
    if(propRight) prop(y, x+1);

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
            n[rowNum][i].d = 1;
            if(rowNum != 0) n[rowNum-1][i].u = 1;
        }
        else continue;
    }
}

void parseLastLine(char * line)
{
    printf("%s\n");
    assert(*line != '\0');
    line += 1;
    int i;
    for(i=0;i<w; i++, line+=2)
    {
        if(*line == ' ')
            n[h-1][i].u = 1;
    }
}
void parseBottomLine(char * line, int rowNum)
{
    assert(*line != '\0');
    int i;
    for(i=0;i<w;i++, line += 2)
    {
        if(*line == ' '){
            n[rowNum][i].l = 1;
            if(i != 0)
                n[rowNum][i-1].r = 1;
        }
            
    }
    
    //for right edge of last one
    if(*line == ' '){
        n[rowNum][w-1].r = 1;
       //n[rowNum][w-1].dist = 1;
    }
}

int main()
{
	FILE *fin=fopen("maze1.in", "r"), *fout=fopen("maze1.out", "w");
	assert (fin!= NULL && fout != NULL);

    int i, j;
    char line[200];

    fscanf(fin, "%d%d ", &w, &h);

        for(i=0;i<h;i++)
        for(j=0;j<w;j++){
            n[i][j].dist = INFINITY;
            n[i][j].known = 0;
        }
    
    for(i=0;i<h; i++)
    {
        fgets(line, 200, fin);
        parseTopLine(line, i);
        fgets(line, 200, fin);
        parseBottomLine(line, i);
    }
    fgets(line, 200, fin);
    parseLastLine(line);

    //mark left and right exits
    for(i=0;i<h;i++)
    {
        if(n[i][0].l){
            n[i][0].dist = 1;
            resetKnown();
            prop(i,0);
        }
        if(n[i][w-1].r){
            n[i][w-1].dist = 1;
            resetKnown();
            prop(i, w-1);
        }
    }

    //mark top and bottom exits

    for(i=0;i<w;i++)
    {
        if(n[0][i].d){
            n[0][i].dist = 1;
            resetKnown();
            prop(0,i);
        }
        if(n[h-1][i].u){
            n[h-1][i].dist = 1;
            resetKnown();
            prop(h-1, i);
        }
    }

    int longest=0;

    for(i=0;i<w;i++)
        for(j=0;j<h;j++)
            longest = max(longest, n[j][i].dist);

    fprintf(fout, "%d\n", longest);
    //printMaze();


	exit(0);
}
