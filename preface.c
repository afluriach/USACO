/*
ID: afluria1
LANG: C
TASK: preface
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX(a,b) (a>b ? a : b);

//0-1
//1-5
//2-10
//3-50
//4-100
//5-500
//6-1000

int numerals[7], highest=0;
char symbols[]={'I', 'V', 'X', 'L', 'C', 'D', 'M'};

int countLetters(int n)
{
	while(n >= 1000)
	{
		n -= 1000;
		numerals[6] ++;
	}
	if(n >= 900)
	{
		numerals[4]++;
		numerals[6]++;
		n -= 900;
	}
	if(n>= 500)
	{
		numerals[5]++;
		n -= 500;
	}
	if(n >= 400)
	{
		numerals[4]++;
		numerals[5]++;
		n -= 400;
	}
	while(n >= 100)
	{
		numerals[4]++;
		n -= 100;
	}
	if(n >= 90)
	{
		numerals[2]++;
		numerals[4]++;
		n -= 90;
	}
	if(n >= 50)
	{
		n -= 50;
		numerals[3]++;
	}
	if(n >= 40)
	{
		numerals[2]++;
		numerals[3]++;
		n -= 40;
	}
	while(n >= 10)
	{
		numerals[2]++;
		n -= 10;
	}
	if(n ==9)
	{
		numerals[0]++;
		numerals[2]++;
		n -= 9;
	}
	if(n >= 5)
	{
		numerals[1]++;
		n -= 5;
	}
	if(n==4)
	{
		n -= 4;
		numerals[0]++;
		numerals[1]++;
	}
	while(n > 0)
	{
		numerals[0]++;
		n--;
	}
}

int main()
{
	int i, n, target;
	FILE *fin = fopen("preface.in", "r"), *fout = fopen("preface.out", "w");
	assert(fin != NULL && fout != NULL);
	fscanf(fin, "%d", &n);
	for(i=1;i<=n;i++)
		countLetters(i);
	for(target=6; numerals[target] == 0; target--)
		;
	for(i=0;i<=target;i++)
	{
		fprintf(fout, "%c %d\n", symbols[i], numerals[i]);
	}
	exit(0);
}