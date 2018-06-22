/*
ID: afluria1
LANG: C
TASK: nocows
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

long long int memo[201][101][2];


long long int tree(int nodes, int height, int considerIncomplete)
{
    if(memo[nodes][height][considerIncomplete] != -1) return memo[nodes][height][considerIncomplete];
    if(nodes > (1 << height)-1 ) return 0; 
    if(nodes == 1){ 
        if(considerIncomplete)
            return height >= 1;
        else return height == 1;
    }

    long long int l, r, count=0;
    for(l=1, r=nodes-2; r>=0; l +=2 , r -= 2)
    {
		if(l==r)
			continue;
         count +=  2*tree(l, height-1, 1)*tree(r, height-1, considerIncomplete);
    }
    count += tree((nodes-1)/2, height-1, considerIncomplete)*tree((nodes-1)/2, height-1, considerIncomplete);
    memo[nodes][height][considerIncomplete] = count;
    return count;
}

int main()
{
	FILE *fin=fopen("nocows.in", "r"), *fout=fopen("nocows.out", "w");
	assert (fin!= NULL && fout != NULL);
	
	
	int i, j, h, n;
	for(i=0;i<201;i++)
		for(j=0;j<101;j++){
			memo[i][j][0] = -1;
			memo[i][j][1] = -1;
        }
			
	fscanf(fin, "%d%d", &n, &h);
	
	fprintf(fout, "%d\n", tree(n, h, 0) % 9901);
	
	exit(0);
}
