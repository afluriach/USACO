/*
ID: afluriac
PROB: frac1
LANG: C
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int gcd(int a, int b)
{
    if(b==0)
        return a;
    else
        return gcd(b, a%b);   
}

typedef struct
{
    int n, d;
} Fraction;

int fractcmp(const void * a, const void * b)
{
     Fraction x = *(Fraction *) a;
     Fraction y = *(Fraction *) b;
    
    float c = 1.0*x.n/x.d, d=1.0*y.n/y.d;
    if(c < d)
        return -1;
    else if(c > d)
        return 1;
    else return 0;
}

int main()
{
       FILE *fin=fopen("frac1.in", "r"), *fout=fopen("frac1.out", "w");
       int i, j, nFracts=2, maxDenom;
       Fraction * arr;
       assert(fin!= NULL && fout != NULL);
       fscanf(fin, "%d", &maxDenom);
       arr = malloc(sizeof(Fraction)*maxDenom*(maxDenom+1)/2);
       
       // 0/1 and 1/1 base cases
       arr[0].n =0;
       arr[0].d =1;
       
       arr[1].n = 1;
       arr[1].d = 1;
       
       for(i=2; i <= maxDenom; i++)
       {
            for(j=1; j < i; j++)
            {
                if(gcd(i, j) ==1)
                {
                    arr[nFracts].n = j;
                    arr[nFracts].d = i;
                    nFracts++;
                }
            }
       }
       qsort(arr, nFracts, sizeof(Fraction), fractcmp);
       
       for(i=0;i<nFracts;i++)
       {
            fprintf(fout, "%d/%d\n", arr[i].n, arr[i].d);
        }
       
       exit(0);
}
