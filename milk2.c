/*
ID: afluria1
LANG: C
TASK: milk2
*/      

#include <stdio.h>

int main()
{
    FILE* fin = fopen("milk2.in", "r");
    FILE* fout = fopen("milk2.out", "w");
    
    short int* arr = calloc(1000000, sizeof(short int));
    int num_farmers, globalstart, globalend, start, end, i, j;
    int crnt, max, maxidle, maxmilk;
    fscanf(fin, "%d", &num_farmers);
    
    fscanf(fin, "%d%d", &start, &end);
    globalstart = start;
    globalend = end;
    
    for(j=start;j<end;j++)
        arr[j] = 1;
    
        
    
    for(i=1;i<num_farmers;i++)
    {
        fscanf(fin, "%d%d", &start, &end);
        
        if(start<globalstart)
            globalstart = start;
            
        if(end>globalend)
            globalend = end;
            
        for(j=start;j<end;j++)
            arr[j] = 1;
    }
    
    for(i=globalstart, crnt=0, max=0; i< globalend; i++)
    {
        if(arr[i])
            crnt++;
        else
        {
            if(crnt > max)
                max = crnt;
            crnt = 0;
        }
    }
    if(crnt > max)
        max = crnt;
    
    maxmilk = max;
    
    for(i=globalstart, crnt=0, max=0; i< globalend; i++)
    {
        if(!arr[i])
            crnt++;
        else
        {
            if(crnt > max)
                max = crnt;
            crnt = 0;
        }
    }
    if(crnt > max)
        max = crnt;
    
    maxidle = max;
    
    fprintf(fout, "%d %d\n", maxmilk, maxidle);
    
    exit(0);
    
}
