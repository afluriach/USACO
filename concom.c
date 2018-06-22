/*
ID: afluria1
TASK: concom
LANG: C
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//op[1][2] = 80;  company a owns 80% of company b

short int p[101][101], o[101][101];

void testown()
{
    int i, j, k;
        for(i=1;i<=100;i++)
    {
        for(j=1;j<=100;j++)
        {
            int sum=0;
            //for relation i -> j
            //for each k, if i owns k, add k's ownership of j
            
            for(k=1;k<=100; k++)
            {
                if(p[i][k] > 50 || o[i][k])
                    sum += p[k][j];
            }
            
            if(sum > 50)
                o[i][j] = 1;
        }
        
    }
    
}

int main()
{
    memset(p, 0, 101*101*sizeof(short int));
    memset(o, 0, 101*101*sizeof(short int));
    
    int nTriples, i, j, k;
    FILE *fin=fopen("concom.in", "r"), *fout=fopen("concom.out", "w");
    assert(fin != NULL && fout != NULL);
    fscanf(fin, "%d", &nTriples);
    
    for(i=0;i<nTriples; i++)
    {
        int a, b, pe;
        fscanf(fin, "%d%d%d", &a, &b, &pe);
        p[a][b] = pe;
        
        //each company owns itself; only flag ones that have been mentioned.
        o[a][a] = 1;
        o[b][b] =1;
    }
    
    for(i=1;i<=100; i++)
    {
        for(j=1;j<=100;j++)
        {
            if(p[i][j] > 50)
                o[i][j] = 1;
        }
    }
    
    for(i=1;i<=100;i++)
    {
        for(j=1;j<=100;j++)
        {
            int sum=0;
            //for relation i -> j
            //for each k, if i owns k, add k's ownership of j
            
            for(k=1;k<=100; k++)
            {
                if(p[i][k] > 50 || o[i][k])
                    sum += p[k][j];
            }
            
            if(sum > 50)
                o[i][j] = 1;
        }
        
    }
    
    for(i=0;i<100;i++)
        testown();
    
    for(i=1;i<=100;i++)
    {
        for(j=1;j<=100;j++)
        {
            if(o[i][j] && i != j)
                fprintf(fout, "%d %d\n", i, j);
        }
    }
    exit(0);
    
}
