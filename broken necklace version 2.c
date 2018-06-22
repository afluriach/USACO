/*
ID: afluria1
LANG: C
TASK: beads
*/

#include <stdio.h>
#define DEBUG 1
int main()
{
    int i, j, max1, max2, bestmax=0, bestpos, nb;
    FILE *fin=fopen("beads.in", "r");
    FILE *fout=fopen("beads.out", "w");
    fscanf(fin, "%d", &nb);
    char target;
    char *beads=malloc(nb);
    
    for(i=0;i<nb;i++)
    {
        if(DEBUG)
        {
            printf("outer loop, i=%d\n", i);
            system("PAUSE");
        }
        
            //count up
            for(j=i, target=beads[j], max1=0;
                beads[j] == target || beads[j] == 'w';
                j=(j+1)%nb, max1++)
                    if(DEBUG)
                        printf("up loop iteration, i=%d, j=%d, target=%c max1=%d\n", i, j, target, max1);
                
            for(j=(i<=0 ? nb-1 : i-1), max2=0, target = beads[j];
                beads[j] == target || beads[j] == 'w';
                j=(j<=0 ? nb-1 : j-1), max2++)
                if(DEBUG)
                        printf("down loop iteration, i=%d, j=%d\n, target=%c max2=%d\n", i, j, target, max2);
                
            if(max1+max2>bestmax)
            {
                bestpos = i;
                bestmax = max1+max2;
                if(DEBUG)
                    printf("new bestpos %d, new bestmax %d\n", bestpos, bestmax);
            }
    }
    fprintf(fout, "%d\n", bestpos);
    if(DEBUG)
        system("PAUSE");
    exit(0);
}
