/*
ID: afluria1
LANG: C
TASK: palsquare
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define DEBUG 0

FILE* fin, *fout;

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
    if(DEBUG)
        fprintf(fout, "%s is a palindrome\n", str);
    return 1;
}

int main()
{
    FILE* fin = fopen("palsquare.in", "r");
    FILE* fout = fopen("palsquare.out", "w");
    assert(fin != NULL && fout != NULL);
    
    int base, i;
    fscanf(fin, "%d", &base);
    
    for(i=1; i<=300;i++)
    {
        if(ispalin(itos(i*i, base)))
        {
            
            fprintf(fout, "%s %s\n", itos(i, base), itos(i*i, base));
        }
    }   
    
    exit(0);
}
