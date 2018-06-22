/*
ID: afluriac
PROB: hamming
LANG: C
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int nCodes, nBits, nDist;
int codes[64], cIndex=0;
int hamDist(int a, int b)
{
    int count, i, x = a ^ b;
    for(i=0, count=0; a > 0 || b > 0; a/=2, b/=2, i++)
    {
        if((x >> i) & 1)
            count ++;
    }
    return count;
}

int inList(int n)
{
    int i;
    for(i=0;i<cIndex; i++)
        if(hamDist(codes[i], n) < nDist)
            return 0;
    return 1;
}

int main()
{
       FILE *fin=fopen("hamming.in", "r"), *fout=fopen("hamming.out", "w");
       assert(fin!= NULL && fout != NULL);
       
       fscanf(fin, "%d %d %d", &nCodes, &nBits, &nDist);
       
       int i, max;
       
       for(i=0, max = 1 << nBits; i < max && cIndex < nCodes; i++)
       {
            if(inList(i))
                codes[cIndex++] = i;
        }
        
        for(i=0;i<nCodes;i++)
        {
         
            if(i%10 != 0)
                fprintf(fout, " ");
            fprintf(fout, "%d", codes[i]);  
               if(i % 10 == 9)
                fprintf(fout, "\n"); 
        }
       if(i % 10 != 0)
            fprintf(fout, "\n");
       
       
       exit(0);
}
