/*
ID: afluria1
LANG: C
TASK: runround
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int check(int n)
{
	int nDigits=0, i, temp, crntPos, nCycles, digits[9], visited[9] = {0,0,0,0,0,0,0,0,0};
	
	while(n > 0){
		digits[nDigits++] = n % 10;
		n /= 10;
	}
	for(i=0;i<nDigits/2;i++)
	{
		temp = digits[i];
		digits[i] = digits[nDigits-1-i];
		digits[nDigits-1-i] = temp;
	}
	
	for(crntPos=0, nCycles=0; nCycles < nDigits; nCycles++)
	{
		crntPos += digits[crntPos];
		crntPos %= nDigits;
		visited[crntPos]++;
	}
	for(i=0;i<nDigits;i++)
		if(visited[i] != 1)
			return 0;
	return 1;
}

int main()
{
	int i, m, ans;
	FILE *fin = fopen("runround.in", "r"), *fout = fopen("runround.out", "w");
	assert(fin != NULL && fout != NULL);
	fscanf(fin, "%d", &m);
	
	for(i=m+1;;i++)
	{
		//sum digits and check that none are zero and all are unique
		int sum=0, digit, crnt=i, digitCheck=1, nDigits=0, digits[10] = {0,0,0,0,0,0,0,0,0,0};

		while(crnt > 0)
		{
			digit = crnt % 10;
			if(digit == 0){
				//printf("Digit checked failed.\n");
				digitCheck=0;
				break;
			}
			else if(!digits[digit])
				digits[digit]++;
			else{
				digitCheck=0;
				break;
			}
			sum += digit;
			crnt /= 10;
			nDigits++;
		}
		if(!digitCheck || sum % nDigits != 0){
			//printf("Divisibility failed. %d digits, sum %d\n", nDigits, sum);
			continue;
		}
			
		if(check(i)){
			ans = i;
			break;
		}
		
	}
	fprintf(fout, "%d\n", ans);
	exit(0);
}