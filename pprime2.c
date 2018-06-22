/*
ID: afluria1
LANG: C
TASK: pprime
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct{
	int len, *arr;
} intList;

intList cPal [9];
intList ncPal[9];
int primes[10000]={2}, pIndex=1;

int log10(int n){
	int i;
	for(i=0;n>0;i++, n/=10)
		;
	return i;
}

int pow10(int exp){
	if(exp == 0)
		return 1;
	else if(exp == 1)
		return 10;
	else if(exp % 2 == 0)
	{
		int x = pow10(exp/2);
		return x*x;
	}
	else
	{
		int x = pow10(exp/2); 
		return x*x*10;
	}
}

void popPrimeList(int max){
	int i, j, isPrime;
	for(i=3; i*i <= max; i++)
	{
		for(j=0, isPrime=1;j<pIndex; j++)
			if(i % primes[j] == 0){
				isPrime=0;
				break;
			}
		if(isPrime)
			primes[pIndex++] = i;
	}
}

void buildPalList(int nDigits, int target){
	int i, j, k;
	if(nDigits > target)
		return;
	else if(nDigits == 1)
	{
		//for 1 digits only, canonical and noncanonical are the same (0 is a valid number)
		cPal[1].len = 10, ncPal[1].len = 10;
		cPal[1].arr = malloc(sizeof(int)*20);
		ncPal[1].arr = cPal[1].arr + 10;
		for(i=0;i<=9;i++)
			cPal[1].arr[i]  = ncPal[1].arr[i] = i;
	}
	else if(nDigits==2)
	{
		cPal[2].len = 9, ncPal[2].len = 10;
		cPal[2].arr = malloc(sizeof(int)*19);
		ncPal[2].arr = cPal[2].arr + 9;
		
		for(i=0;i<9; i+=1)
			cPal[2].arr[i] = (i+1)*11;
		for(i=0;i<10;i++)
			ncPal[2].arr[i] = i*11;
	}
	//recursively build palindromes based on palindromes of n-2 digits
	else
	{
		//prepare intList for nDigits
		
		cPal[nDigits].len = 9*ncPal[nDigits-2].len;
		ncPal[nDigits].len = 10*ncPal[nDigits-2].len;
		cPal[nDigits].arr = malloc(sizeof(int)*cPal[nDigits].len);
		ncPal[nDigits].arr = malloc(sizeof(int)*ncPal[nDigits].len);
		
		//fill cPal list
		for(i=1, k=0; i<=9;i++)
		{
			for(j=0; j<ncPal[nDigits-2].len; j++)
			{
				cPal[nDigits].arr[k++] = i*pow10(nDigits-1)+i+10*ncPal[nDigits-2].arr[j];
			}
		}
		
		//fill ncPal list
		for(i=0, k=0; i<=9;i++)
		{
			for(j=0; j<ncPal[nDigits-2].len; j++)
			{
				ncPal[nDigits].arr[k++] = i*pow10(nDigits-1)+i+10*ncPal[nDigits-2].arr[j];
			}
		}
	}
	buildPalList(nDigits+1, target);
} 

int isPrime(int n){
	int i;
	for(i=0;i<pIndex && primes[i]*primes[i] <= n;i++)
		if(n % primes[i] == 0)
			return 0;
	return 1;
}

int main()
{
	int i, j, min, max, complete=0;
	FILE *fin=fopen("pprime.in", "r"), *fout=fopen("pprime.out", "w");
	fscanf(fin, "%d %d", &min, &max);
	popPrimeList(max);
	buildPalList(1, log10(max));
	for(i=1; i<=8 && !complete; i++)
	{
		for(j=0;j<cPal[i].len; j++)
		{
			if(cPal[i].arr[j] < min)
				continue;
			if(cPal[i].arr[j] > max){
				complete = 1;
				break;
			}
			if(isPrime(cPal[i].arr[j]))
				fprintf(fout, "%d\n", cPal[i].arr[j]);
		}
	}

	exit(0);
}