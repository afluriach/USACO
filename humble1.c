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
#define MAX 100000000

int primes[MAX_PRIMES], nPrimes, target;
char humble[MAX/8];

int isHumble(int n){
    return (humble[n/8] >> n%8) &1;
}

void setHumble(int n){
    humble[n/8] |= 1<<n%8;
}

int main()
{
	FILE *fin=fopen("humble.in", "r"), *fout=fopen("humble.out", "w");
	assert (fin!= NULL && fout != NULL);
    int i;
    fscanf(fin, "%d %d", &nPrimes, &target);

    for(i=0;i<nPrimes;i++)
        fscanf(fin, "%d", primes+i);

    //base case, set the primes to be humble

    for(i=0;i<nPrimes;i++)
        setHumble(primes[i]);

    //go through the sequence. if a number is humble, set all prime mutliples
    //of it to humble

    int count=0, j;
    for(i=2;i<MAX && count < target;i++)
        if(isHumble(i)){
            count++;
            for(j=0;j<nPrimes;j++)
                if(primes[j]*i < MAX)
                    setHumble(primes[j]*i);
        }
    fprintf(fout, "%d\n", i-1);

	exit(0);
}
