/*
ID: afluria1
TASK: zerosum
LANG: C
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SPACE 0
#define PLUS 1
#define MINUS 2

char convert(int i)
{
    if(i==PLUS)
        return '+';
    else if (i==MINUS)
        return '-';
    else if (i==SPACE)
        return ' ';
    else
        assert(0);
}


void printState(FILE * fout, int * state, int n)
{
    int i;
    for(i=1;i<n;i++)
        fprintf(fout, "%d%c", i, convert(state[i]));
    fprintf(fout, "%d\n", n);
}   


int nDigits(int pos, int * state)
{
    int i, count;
    for( i=pos, count=1; state[i] ==SPACE; i++, count++)
        ;
    return count;
}

int value(int pos, int * state, int n)
{
    int i=pos, val=pos;
    while(state[i] == SPACE && i < n)
    {
        val = val * 10 + ++i;
    }
    return val;
}

int terniter(int * state, int n)
{
    //printState(stdout, state, n);
      // printf("sum: %d\n", sum(state, n));
    int i;
    state[n-1]++;
    for(i=n-1;i>0; i--)
    {
        if(state[i] > 2)
        {
            state[i] = 0;
            state[i-1]++;
        }
        else break;
    }
 
    //system("PAUSE");
    return state[0] > 0;

}

int sum(int * state, int n)
{
    int i,sum;
   // printf("sum is %d...\n", sum=value(1, state, n));
    for(i=nDigits(1, state), sum=value(1, state, n);i<n; i+= nDigits(i+1, state))
    {
     //   printf("%d ", state[i]);
        switch(state[i])
        {
            case PLUS:
         //       printf("plus %d\n", value(i+1, state, n));
                sum += value(i+1, state, n);
                break;
            case MINUS:
         //       printf("minus %d\n", value(i+1, state, n));
                sum -= value(i+1, state, n);
                break;
            default:
                assert(0); 
        }
    }
    return sum;
}



int main()
{
    FILE *fin=fopen("zerosum.in", "r"), *fout=fopen("zerosum.out", "w");
    assert(fin != NULL && fout != NULL);
    int i, n, state[10];
    memset(state, 0, 10*sizeof(int));
    
    fscanf(fin, "%d", &n);
    
    while(!terniter(state, n))
    {
        if(sum(state, n) ==0)
            printState(fout, state, n);
    }
    exit(0);
}
