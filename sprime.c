/*
ID: afluria1
LANG: C
TASK: sprime
*/


#include <stdio.h>
#include <stdlib.h>

#define MAXPRIMES 100000

int singleDigitPrimes [] = {2,3,5,7};
int odds [] = {1,3,5,7,9};
int primes[MAXPRIMES] ={2};
int nPrimes=1;

FILE *fin, *fout;

int isPrimeOptimized(int n)
{
	int i;
	for(i=0;i<nPrimes && primes[i]*primes[i] <= n; i++)
	{
		if(n % primes[i] ==0)
			return 0;
	}
	return 1;
}

void buildPrimeList(int max)
{
	int i, j;
	for(i=2;i<max;i++)
	{
		int isPrime=1;
		for(j=0;j<nPrimes;j++)
		{
			if(i%primes[j] == 0)
			{
				isPrime=0;
				break;
			}
		}
		if(isPrime)
			primes[nPrimes++] = i;
	}
	if(nPrimes > MAXPRIMES)
		printf("Error: too many primes.\n");
//	for(i=0;i<nPrimes;i++)
//		printf("%d\n", primes[i]);
}

void iterPrimes(int crntDigits, int targetDigits, int n)
{
	//printf("iter call: ndigits:%d, target: %d, currnet n: %d\n", crntDigits, targetDigits, n);
	int i;
	if(crntDigits==1)
	{
		for(i=0;i<4; i++)
		{
			iterPrimes(2, targetDigits, singleDigitPrimes[i]);
		}
	}
	else if(crntDigits == targetDigits+1)
	{
		if(isPrimeOptimized(n))
			fprintf(fout, "%d\n", n);
	}
	else
	{
		for(i=0;i<5; i++)
		{
			int crnt = 10*n+odds[i];
			if(isPrimeOptimized(crnt))
				iterPrimes(crntDigits+1, targetDigits, crnt);
//			else printf("%d is not prime\n", crnt);
		}
	}
	
	
			
}

int main()
{
	fin = fopen("sprime.in", "r"), fout = fopen("sprime.out", "w");
	
	int nDigits;
	fscanf(fin, "%d", &nDigits);
	buildPrimeList(10000);
	iterPrimes(1, nDigits, 0);
	fclose(fout);
	exit(0);
}
