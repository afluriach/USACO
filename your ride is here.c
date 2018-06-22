/*
ID: afluria1
LANG: C
TASK: ride
*/

#include <stdio.h>

int letterposnum(char c)
{
    c = tolower(c);
    return  c - 'a' + 1;
}

int numberize(char* s)
{
    int i, product =1;
    for(i=0;s[i] != '\0'; i++)
    {
        product *= letterposnum(s[i]);
    }
    return product;
}

int main()
{
    FILE* fin = fopen("ride.in", "r");
    FILE* fout = fopen("ride.out", "w");
    if(fin == NULL || fout == NULL)
        exit(0);
    int cometprod, groupprod;
    char name[32];
    fscanf(fin, "%s", name);
    cometprod = numberize(name);
    fscanf(fin, "%s", name);
    groupprod = numberize(name);
    if(groupprod % 47 == cometprod % 47)
        fprintf(fout, "GO\n");
    else
        fprintf(fout, "STAY\n");
    
    exit(0);
}
