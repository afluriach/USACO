/*
ID: afluria1
LANG: C
TASK: beads
*/

#include <stdio.h>
#define DEBUG 0
int main()
{
    int i, j, bestmax=0, numbeads, crntbest, start, total;
    char *beads, target;
    
    FILE* fin = fopen("beads.in", "r");
    FILE* fout = fopen("beads.out", "w");
    
    fscanf(fin, "%d ", &numbeads);
    beads=malloc(numbeads);
    
    if(DEBUG)
        printf("numbeads: %d\n", numbeads);
    
    for(i=0;i<numbeads;i++)
    {
        fscanf(fin, "%c", &(beads[i]));
    }
    
    for(i=0;i<numbeads;i++)
    {
        if(DEBUG)
            printf("Examining pos %d\n", i);
        crntbest=0;
        target='n';
        //wraparound=0;
        total=0;
        
        j=(i<1) ? numbeads-1 : i-1;
        start=j;
    
        //count down  
        
        if(DEBUG)
                printf("going down\n");
          
        while(total<numbeads)
        {/*
            if(start != j)
                wrapflag =1;
            
            if(wrapflag && start==j)
            {
                wraparound=1;
                break;
            }
            */
            
            if(DEBUG)
                printf("going down, examining bead %d, color %c\n", j, beads[j]);
            if(target=='n' && beads[j] != 'w')
            {
                target = beads[j];
                if(DEBUG)
                {
                    printf("Target assigned color %c\n", beads[j]);
                    system("PAUSE");
                }
                    
            }
            
            if(beads[j] ==target || beads[j] == 'w' && total < numbeads)
            {
                crntbest++;
                total++;
                j=(j<1) ? numbeads-1 : j-1;
            }
            else break;
        }
        
        
        if(DEBUG)
        {
            printf("stopped at %d, bead color %c\n", j, beads[j]);
            system("PAUSE");
        }
        
        target='n';
        j=i;
        //wrapflag=0;
        
        if(DEBUG)
            printf("going up\n");
        
        while(total<numbeads)
        {
            /*
            if(start != j)
                wrapflag =1;
            
            if(wrapflag && start==j)
            {
                wraparound=1;
                break;
            }
            */
            
            if(DEBUG)
                printf("going up, examining bead %d, color %c\n", j, beads[j]);
            if(target=='n' && beads[j] != 'w')
            {
                target = beads[j];
                if(DEBUG)
                    printf("Target assigned color %c\n", beads[j]);
            }
            
            if(beads[j] == target || beads[j] == 'w' && total < numbeads)
            {
                crntbest++;
                total++;
                j = (j+1)%numbeads;
            }
            else break;
        }
        
        
        if(DEBUG)
        {
            printf("stopped at %d, bead color %c\n", j, beads[j]);
            system("PAUSE");
        }
        
        if(crntbest > bestmax)
        {
            if(DEBUG)
                printf("non wraparound, new best %d\n", crntbest);
            bestmax = crntbest;
        }
        
        
    }
                        
    
    fprintf(fout, "%d\n", bestmax);
    exit(0);
}
