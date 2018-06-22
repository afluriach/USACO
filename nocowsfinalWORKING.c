/*
ID: afluria1
LANG: C
TASK: nocows
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

 int treeMemo[201][101];
int shortMemo[201][101];

int shortTree(int nodes, int height)
{
    if(height == 0 || nodes == 0)
        return 0;
    if(nodes == 1 )
        return 1;
    if(height == 1)
        return nodes==1;
    assert(nodes > 1 && height > 1);
    if(shortMemo[nodes][height] != -1)
        return shortMemo[nodes][height];
    int l, r;
    long long int count=0;
    for(l=1, r=nodes-2; r > 0; l += 2, r -= 2)
        count += shortTree(l, height-1)*shortTree(r, height-1);
    count %= 9901;
    shortMemo[nodes][height] = count;
    return count;
}

int tree(int nodes, int height)
{    
    if(height==1)
         return nodes == 1;
    if(height==0)
        return 0;

    if(treeMemo[nodes][height] != -1)
        return treeMemo[nodes][height];

    long long int l, r, count=0;
    for(l=1, r=nodes-2; r>0; l +=2 , r -= 2)
    {
         count +=  tree(l, height-1)*shortTree(r, height-2);
         count +=  shortTree(l, height-2)*tree(r, height-1);
         count += tree(l, height-1)*tree(r, height-1);
    }
    count %= 9901;
   treeMemo[nodes][height] = count;
    return count;
}

int main()
{
	FILE *fin=fopen("nocows.in", "r"), *fout=fopen("nocows.out", "w");
	assert (fin!= NULL && fout != NULL);
	
	
	int i, j, h, n;
	for(i=0;i<201;i++)
		for(j=0;j<101;j++){
			shortMemo[i][j] = -1;
			treeMemo[i][j] = -1;
        }
			
	fscanf(fin, "%d%d", &n, &h);
	
	fprintf(fout, "%d\n", tree(n, h) % 9901);
	
	exit(0);
}
