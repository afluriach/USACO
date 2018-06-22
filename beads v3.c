/*
ID: afluria1
LANG: C
TASK: beads
*/

#include <stdio.h>
#define DEBUG 1

//all items below pos go in the down strand in reverse order, all items >= go into
//up in sequential order
int reorder(char* beads, int nb, char* down, char* up, int pos)
{
    int i;
    for(i=0;i<nb;i++)
        up[i] = beads[(i+pos)%nb];
    for(i=0;i<nb;i++)
        down[i] = beads[(nb+pos-i)%nb];
}

int main()
{
    int i, j, k, nb, downcount, upcount, maxcount=0;
    char *beads, *downstrand, *upstrand, target;
    FILE* fin = fopen("beads.in", "r");
    FILE* fout = fopen("beads.out", "w");
    
    fscanf(fin, "%d", &nb);
    beads = malloc(nb), downstrand=malloc(nb), upstrand=malloc(nb);
    
    for(i=0;i<nb;i++)
    {
        reorder(beads, nb, downstrand, upstrand, i);
        downcount=0, upcount=0;
        
        target = downstrand[0];
        for(j=0;downstrand[j]==target || downstrand[j] == 'w'; j++, downcount++)
            ;
            
        if(DEBUG)
        {
            printf("downcount: %d; downstrand: ", downcount);
            for(k=0;k<nb;k++)
                printf("%c", downstrand[k]);
            printf("\n");
        }
        
        target = upstrand[0];
        for(j=0;upstrand[j]==target || upstrand[j] == 'w'; j++, upcount++)
            ;
            
        if(DEBUG)
        {
            printf("upcount: %d; upstrand: ", upcount);
            for(k=0;k<nb;k++)
                printf("%c", upstrand[k]);
        }
        
        if(downcount+upcount > maxcount)
            maxcount = downcount + upcount;
    }
    
    fprintf(fout, "%d\n", maxcount);
    system("PAUSE");
    exit(0);
}
