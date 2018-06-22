/*
ID: afluria1
LANG: C
TASK: crypt1
*/

#include <stdio.h>
#define DEBUG 0
#include <assert.h>

int count=0;

int readlist(FILE* fin, int *digits);
int testint(int num, int * list);

int multiply(int *factor1, int *factor2, int *digits)
{
    int factor1int = factor1[0] * 100 + factor1[1] * 10 + factor1[2];
    int part1 = factor1int * factor2[1];
    int part2 = factor1int * factor2[0];
    int product = factor1int * (factor2[0] * 10 + factor2[1]);
    if(testint(factor1int, digits) && testint(part1, digits) && testint(part2, digits)
        && testint(product, digits) && part1>= 100 && part1<= 999 && part2 >= 100
        && part2 <=999 && product >= 1000 && product <= 9999)
            count++;
}

int make1st(int index, int target, int *digits, int * factor)
{
    int i, j;
    if(index >= target)
    {
        int factor2[2];
        /*
        for(i=0;i<target;i++)
            printf("%d", factor[i]);
        printf("\n");
        */
        for(i=0;i<10;i++)
        {
            if(digits[i])
                for(j=0;j<10;j++)
                {
                    if(digits[j])
                    {
                        factor2[0]=i, factor2[1]=j;
                         multiply(factor, factor2, digits);
                    }
                }
        }
                
    }
    else
    {
        for(i=0;i<10;i++)
        {
            if(digits[i])
            {
                factor[index] = i;
                make1st(index+1, target, digits, factor);
            }
        }
    }
}

int readlist(FILE* fin, int *digits)
{
    assert(fin != NULL);
    int i, n, dummy;
    fscanf(fin,"%d", &n);
    for(i=0;i<n;i++)
    {
        fscanf(fin, "%d", &dummy);
        assert(dummy >=0), assert(dummy <= 9);
        digits[dummy] = 1;
    }
}        

int testint(int num, int * list)
{
    assert(num >=0);
    while (num > 10)
    {
        if(!list[num%10])
            return 0;
        else
            num /= 10;
    }
    if(!list[num])
        return 0;
    else return 1;
}



int main()
{
    FILE* fin = fopen("crypt1.in", "r");
    FILE* fout = fopen("crypt1.out", "w");
    assert(fin != NULL && fout != NULL);
    
    int digits[10], factor1[3], i;
    for(i=0;i<10;i++)
        digits[i] = 0;
    readlist(fin, digits);
    
    make1st(0, 3, digits, factor1);
    
    fprintf(fout, "%d\n", count); 
    
    exit(0);
}
