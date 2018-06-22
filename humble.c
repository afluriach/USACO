/*
ID: afluria1
LANG: C
TASK: humble
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define MAX_PRIMES 100
#define MAX_HUMBLE 100000

int nPrimes, target, nHumble=0, h[MAX_HUMBLE+1];

typedef struct
{
    int prime, value, h;
} Prime;

Prime primes[MAX_PRIMES];
Prime * heapArr[MAX_PRIMES+1];
int heapCount;

void percDown(int n){
    if(n > heapCount)
        return;
    int swapPos = n;
    if(n*2 <= heapCount && heapArr[n*2]->value < heapArr[swapPos]->value)
        swapPos = n*2;
    if(n*2+1 <= heapCount && heapArr[n*2+1]->value < heapArr[swapPos]->value)
        swapPos = n*2+1;
    if(swapPos != n)
    {
        Prime * temp = heapArr[swapPos];
        heapArr[swapPos] = heapArr[n];
        heapArr[n] = temp;
        percDown(swapPos);
    }
}

void percUp(int n){
    assert(n >= 1);
    if(n ==1)
        return;
    if(heapArr[n]->value < heapArr[n/2]->value )
    {
        Prime * temp = heapArr[n];
        heapArr[n] = heapArr[n/2];
        heapArr[n/2] = temp;
        percUp(n/2);
    }
}

int getAndIncrement(){
    int returnValue =  heapArr[1]->value;
    Prime * readd = heapArr[1];
    assert(readd->h >= 0);
    assert(readd->h <= nHumble);
    readd->h++;
    if(nHumble ==0 || h[nHumble] != returnValue)
        h[++nHumble] = returnValue;
    readd->value = readd->prime * h[readd->h];
    heapArr[1] = heapArr[heapCount];
    heapCount --;
    percDown(1);
    heapArr[++heapCount] = readd;
    percUp(heapCount);
    return returnValue;
}


int main()
{
	FILE *fin=fopen("humble.in", "r"), *fout=fopen("humble.out", "w");
	assert (fin!= NULL && fout != NULL);
    int i;
    fscanf(fin, "%d %d", &nPrimes, &target);

    for(i=0;i<nPrimes;i++){
        fscanf(fin, "%d", &primes[i].prime);
        primes[i].value = primes[i].prime;
        primes[i].h=0;
        heapArr[++heapCount] = primes+i;
        percUp(heapCount);
    }

    int prev=0, current;

    for(i=1;i<=target;i++)
    {
        current = getAndIncrement();
        printf("The %d th humble number is %d.\n", i, current);
        if(current == prev)
            i--;
        prev = current;
    }

   fprintf(fout, "%d\n", current);

	exit(0);
}
