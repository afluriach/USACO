/*
ID: afluria1
LANG: C
TASK: pprime
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//table of all palindromes of a certain number of digits; array 0 is for canonical, 1 for noncanonical

int * pal[10][2];
//int pal[100000], pIndex=0, palPartition[10][2], nonCanPal[1000], ncpIndex=0, ncPalPartition[10][2];
int primes[10000],primeIndex=0;

int oneDigit [] = {10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int twoDigitCanonical [] = {9, 11, 22, 33, 44, 55, 66, 77, 88, 99};

int pow10(int exp)
{
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

int twoDigitNonCanonical [] = {10, 00, 11, 22, 33, 44, 55, 66, 77, 88, 99};
//returns an array of palindromes for a specified number of digits, index 0 is the number of following palindromes

void popPalList(int nDigits)
{
	int * ncArr = pal[nDigits-2][1]+1;
	int ncCount = pal[nDigits -2][1][0];
	pal[nDigits][0] = malloc(9*ncCount +1);
	pal[nDigits][1] = malloc(10*ncCount + 1);
	pal[nDigits][0][0] = 9*ncCount;
	pal[nDigits][1][0] = 10*ncCount;
	int * crntC = pal[nDigits][0]+1;
	int * crntNC = pal[nDigits][1]+1;
	
	int i, j, count;
	
	//populate canonical list
	for(i=1, count=0; i<= 9; i++)
	{
		for(j=0; j < ncCount; j++)
		{
			crntC[count++] = i*pow10(nDigits-1)+i+ncArr[j];
		}
	}
	
		//populate noncanonical list
	for(i=0, count=0; i<= 9; i++)
	{
		for(j=0; j < ncCount; j++)
		{
			crntNC[count++] = i*pow10(nDigits-1)+i+ncArr[j];
		}
	}
	
}



void popPrimeList(int max)
{
	int i;
	for(i=2; i <= max; i++)
	{
		if(isPrime(i))
			primes[primeIndex++] = i;
	}
}

int isPal(int n)
{
	short int digits[10], i, j, nDigits;
	for(i=0, nDigits=0; n != 0; i++, nDigits++)
	{
		digits[i] = n % 10;
		n /= 10;
	}
	for(i=0, j=nDigits-1; i <= j; i++, j--)
		if(digits[i] != digits[j])
			return 0;
	return 1;
}



int isPrime(int n)
{
	int i;
	for(i=2; i*i <= n; i++)
		if(n % i == 0)
			return 0;
	return 1;
}

int isPrimeOptimized(int n)
{
	int i;
	for(i=0; i < primeIndex && primes[i] < n; i++)
		if(n % primes[i] == 0)
			return 0;
	return 1;
}

int main()
{
	FILE *fin = fopen("pprime.in", "r"), *fout = fopen("pprime.out", "w");
	assert(fin != NULL && fout != NULL);
	int i, j, count, min, max, *crnt;
	fscanf(fin, "%d %d", &min, &max);
	popPrimeList(10000);
	printf("prime list populated\n");
	
	pal[1][0] = oneDigit;
	pal[1][1] = oneDigit;
	pal[2][0] = twoDigitCanonical;
	pal[2][1] = twoDigitNonCanonical;
	
	for(i=3; i <= 7; i++)
	{
		popPalList(i);
	}
	
	for(i=1; i <=7; i++)
	{
		for(count=pal[i][0][0], j=0, crnt=pal[i][0]+1; j < count;j++)
		{
			if(crnt[j] < min || crnt[j] > max)
				continue;
			if(isPrimeOptimized(crnt[j]))
				fprintf(fout, "%d\n", crnt[j]);
		}
	}
	exit(0);
}