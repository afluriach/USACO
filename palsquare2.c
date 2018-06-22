/*
ID: afluria1
LANG: C
TASK: dualpal
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG 0


char *itos(int n, int b)
{
    char* s = malloc(20), *s2=malloc(20);
	static char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVQXYZ";
	int i=0, sign, slen;
    
	if ((sign = n) < 0)
		n = -n;

	do {
		s[i++] = digits[n % b];
	} while ((n /= b) > 0);

	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';

	
    for(i=strlen(s)-1, slen=strlen(s); i>=0; i--)
        s2[slen-i-1]=s[i];
    
    s2[slen]='\0';
	return s2;
}

int ispalin(char* str)
{
    int i;
    for(i=0; i< strlen(str)/2;i++)
    {
        if(str[i] != str[strlen(str) - i - 1])
            return 0;
    }
    return 1;
}

int main()
{
    FILE* fin = fopen("dualpal.in", "r");
    FILE* fout = fopen("dualpal.out", "w");
    
    int base, start, i, j, totalfound=0, crntfound=0;
    
    fscanf(fin, "%d%d", &base, &start);
    
    for(i=start+1; totalfound < base;i++)
    {
        for(crntfound=0, j=2; crntfound<2 && j<= 10;j++)
        {
            //for each base j of int i:
            //increment crnt if it is a palindrome
            //print out i in base 10 and increment total found
            //if crntfound reaches 2 in this loop
            
            if(ispalin(itos(i, j)))
            {
                if(DEBUG)
                    fprintf(fout, "%s\n", itos(i, j));
                crntfound++;
            }
            if(crntfound >= 2)
            {
                totalfound++;
                fprintf(fout, "%d\n", i);
                break;
            }
        }
    }
    exit(0);   
}
