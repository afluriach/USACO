/*
ID: afluria1
LANG: C
TASK: milk
*/

#include <stdio.h>
#define MAXFARMERS 5000
#include <assert.h>

/*****************************

*****************************/

void print(long int f[][2], int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("%ld %ld\n", f[i][0], f[i][1]);
    }
}

int sort(const void* a, const void* b)
{
    long int *x = a;
    long int *y = b;
    
    if(x[0] < y[0])
        return -1;
    else if (x[0] > y[0])
        return 1;
    else return 0;
}

int main()
{
    FILE* fin = fopen("milk.in", "r");
    FILE* fout = fopen("milk.out", "w");
    
    long int i, temp, required, numfarmers, cost=0;
    
    long int farmer[5000][2];
    //[i][0] is the farmers id, [i][1] is the amount availible
    
    fscanf(fin, "%ld%ld", &required, &numfarmers);
    
    for(i=0;i<numfarmers;i++)
    {
        fscanf(fin, "%ld%ld", &(farmer[i][0]), &(farmer[i][1]));
    }
    
    //print(farmer, numfarmers);
    
     qsort(farmer, numfarmers, 2*sizeof(long int), sort); 
     
     //print(farmer, numfarmers);
     
     
     for(i=0; required > 0;i++)
     {
        assert(i < numfarmers); 
        if(farmer[i][1] < required)
        {
             cost += farmer[i][0] * farmer[i][1];
             required -= farmer[i][1];
        }
        else
        {
            temp = required;
            required = 0;
            cost += temp * farmer[i][0];
        }
    }
    
    fprintf(fout, "%ld\n", cost);
    
    exit(0);
    
}
