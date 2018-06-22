/*
ID: afluria1
LANG: C
TASK: fracdec
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX 1000000
int main()
{
    int a,b,i, j, k, repeating=0, repeatStart, repeatEnd;
	FILE *fin=fopen("fracdec.in", "r"), *fout=fopen("fracdec.out", "w");
	assert (fin!= NULL && fout != NULL);
    fscanf(fin, "%d%d", &a, &b);

    //the divisor and remainder at each position after the decimal point
    int d[MAX],  rSeen[MAX];

    for(i=0;i<MAX;i++)
        rSeen[i] = -1;

    //first print the whole number portion.
    int nc = fprintf(fout, "%d.", (a/b));

    a %= b;
    a *= 10;
    
    for(i=0;;i++)
    {
        rSeen[a] = i;
        //printf("%d/%d, %d %d\n", a,b, a/b, a%b);
        d[i] = a/b;
        a %= b;
        a *= 10;

        if(a==0)
            break;
        if(rSeen[a] >= 0)
        {

            repeating=1;
            repeatStart=rSeen[a];
            repeatEnd=i;
            break;
        }
    }

    if(!repeating)
    {
        repeatStart = -1;
        repeatEnd = i + 1;
    }
    int openParentPrinted=0;
    for(j=0;j<=i;j++)
    {
        if(j == repeatStart){
            fprintf(fout, "(");
            openParentPrinted = 1;
        }
        fprintf(fout, "%d", d[j]);
        if(j==repeatEnd){
            fprintf(fout, ")");
        }
        if(j % 76 == 75-nc - openParentPrinted)
            fprintf(fout, "\n");
    }
        fprintf(fout, "\n");
    exit(0);
}
